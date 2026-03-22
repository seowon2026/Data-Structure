#!/bin/bash

read -p "(데이터구조) 커밋 메시지: " msg

# 입력이 비었으면 기본 메시지 사용
if [ -z "$msg" ]; then
    msg="2Grade Data-Structure update ($(date '+%Y-%m-%d %H:%M:%S'))"
fi

git add .
git commit -m "$msg"
git push