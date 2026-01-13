# Auto sync to GitHub

# 如果没有变更，直接退出
if (-not (git status --porcelain)) {
    Write-Host "No changes to commit"
    exit 0
}

$time = Get-Date -Format "yyyy-MM-dd HH:mm:ss"

git add -A
git commit -m "Auto sync @ $time"
git pull origin main --rebase
git push origin main
