#!/bin/bash

# Kiểm tra xem có thay đổi chưa
if ((git status --porcelain | Select-String -Pattern "\S").Count -gt 0) {
    # Nếu có thay đổi, thực hiện commit và push
    Write-Host "Changes detected. Committing and pushing..."
    git add .
    git commit -m "Automatic commit on $(Get-Date -Format yyyy-MM-dd)"
    git push origin main
} else {
    Write-Host "No changes detected."
}
