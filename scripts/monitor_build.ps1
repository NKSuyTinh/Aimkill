param(
    [string]$Token = "",
    [string]$Owner = "NKSuyTinh",
    [string]$Repo = "Aimkill",
    [string]$CommitSha = ""
)

if (-not $Token) {
    $tokenPath = Join-Path $PSScriptRoot "..\github_token.txt"
    if (Test-Path $tokenPath) {
        $Token = (Get-Content $tokenPath -Raw).Trim()
    }
}

[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

$headers = @{
    "Authorization" = "token $Token"
    "Accept"        = "application/vnd.github+json"
    "User-Agent"    = "Aimkill-Build-Watcher"
}

Write-Host "================================================================" -ForegroundColor Cyan
Write-Host "     THEO DOI QUA TRINH BUILD APK TREN GITHUB ACTIONS" -ForegroundColor Cyan
Write-Host "================================================================" -ForegroundColor Cyan
Write-Host "[*] Repository : $Owner/$Repo" -ForegroundColor Yellow
if ($CommitSha) {
    Write-Host "[*] Commit SHA : $CommitSha" -ForegroundColor Yellow
}
Write-Host "[*] Dang tim workflow run..." -ForegroundColor Yellow

$runId = $null
$runNumber = $null
$runUrl = $null
$startTime = Get-Date

# Find the run
for ($i = 0; $i -lt 30; $i++) {
    try {
        $uri = "https://api.github.com/repos/$Owner/$Repo/actions/runs?per_page=5"
        $resp = Invoke-RestMethod -Uri $uri -Headers $headers -Method Get
        $runs = $resp.workflow_runs

        if ($CommitSha) {
            $matchingRun = $runs | Where-Object { $_.head_sha -eq $CommitSha } | Select-Object -First 1
            if ($matchingRun) {
                $runId = $matchingRun.id
                $runNumber = $matchingRun.run_number
                $runUrl = $matchingRun.html_url
                break
            }
        } else {
            if ($runs.Count -gt 0) {
                $runId = $runs[0].id
                $runNumber = $runs[0].run_number
                $runUrl = $runs[0].html_url
                break
            }
        }
    } catch {
        # ignore retry errors
    }
    Start-Sleep -Seconds 2
}

if (-not $runId) {
    Write-Host "[!] Chua tim thay workflow run. Vui long kiem tra tai: https://github.com/$Owner/$Repo/actions" -ForegroundColor Red
    exit 1
}

Write-Host "[+] Da ket noi toi Workflow Run #$runNumber (ID: $runId)" -ForegroundColor Green
Write-Host "[+] Theo doi truc tiep tai: $runUrl" -ForegroundColor Cyan
Write-Host ""

$lastStepName = ""
while ($true) {
    try {
        $runUri = "https://api.github.com/repos/$Owner/$Repo/actions/runs/$runId"
        $run = Invoke-RestMethod -Uri $runUri -Headers $headers -Method Get
        
        $status = $run.status
        $conclusion = $run.conclusion

        # Get jobs and current step
        $jobsUri = "https://api.github.com/repos/$Owner/$Repo/actions/runs/$runId/jobs"
        $jobsResp = Invoke-RestMethod -Uri $jobsUri -Headers $headers -Method Get
        $currentJob = $jobsResp.jobs | Select-Object -First 1
        
        $stepInfo = ""
        if ($currentJob -and $currentJob.steps) {
            $activeStep = $currentJob.steps | Where-Object { $_.status -eq "in_progress" } | Select-Object -Last 1
            if ($activeStep) {
                $stepInfo = " -> Step: $($activeStep.name)"
            }
        }

        $elapsed = [math]::Round(((Get-Date) - $startTime).TotalSeconds)
        $min = [math]::Floor($elapsed / 60)
        $sec = $elapsed % 60
        $timeStr = "{0:D2}:{1:D2}" -f [int]$min, [int]$sec

        if ($status -eq "completed") {
            Write-Host ""
            if ($conclusion -eq "success") {
                Write-Host "================================================================" -ForegroundColor Green
                Write-Host "       [THANH CONG] BUILD APK DA HOAN TAT XUAT SAC!            " -ForegroundColor Green
                Write-Host "================================================================" -ForegroundColor Green
                Write-Host ""
                $releaseTag = "v1.0.$runNumber"
                $apkUrl = "https://github.com/$Owner/$Repo/releases/download/$releaseTag/Onyx%20Aimkill.apk"
                $releasePageUrl = "https://github.com/$Owner/$Repo/releases/tag/$releaseTag"
                $allReleasesUrl = "https://github.com/$Owner/$Repo/releases"

                Write-Host "[★] LINK TAI APK TRUC TIEP:" -ForegroundColor Yellow
                Write-Host "    $apkUrl" -ForegroundColor White
                Write-Host ""
                Write-Host "[★] TRANG GITHUB RELEASE:" -ForegroundColor Yellow
                Write-Host "    $releasePageUrl" -ForegroundColor White
                Write-Host ""
                Write-Host "[★] TRANG ACTIONS ARTIFACTS:" -ForegroundColor Yellow
                Write-Host "    $runUrl" -ForegroundColor White
                Write-Host ""
                Write-Host "[*] Dang tu dong mo trinh duyet den link tai APK..." -ForegroundColor Cyan
                Start-Process $releasePageUrl
                exit 0
            } else {
                Write-Host "================================================================" -ForegroundColor Red
                Write-Host "       [THAT BAI] BUILD GAP LOI! (Ket qua: $conclusion)        " -ForegroundColor Red
                Write-Host "================================================================" -ForegroundColor Red
                Write-Host "[*] Xem chi tiet log loi tai:" -ForegroundColor Yellow
                Write-Host "    $runUrl" -ForegroundColor White
                exit 1
            }
        } else {
            Write-Host ("`r[*] [$timeStr] Trang thai: {0}{1}..." -f $status, $stepInfo) -NoNewline -ForegroundColor Yellow
        }
    } catch {
        # ignore transient network error
    }
    Start-Sleep -Seconds 6
}
