#!/bin/bash
set -euo pipefail

# 현재 사용자의 기본 셸 감지
CURRENT_SHELL=$(basename "${SHELL:-/bin/bash}")

case "$CURRENT_SHELL" in
    zsh)
        RC_FILE="$HOME/.zshrc"
        SHELL_NAME="Zsh"
        ;;
    bash)
        RC_FILE="$HOME/.bashrc"
        SHELL_NAME="Bash"
        ;;
    *)
        echo "지원되지 않는 셸입니다: $CURRENT_SHELL"
        echo "Bash 또는 Zsh 사용자만 지원됩니다."
        exit 1
        ;;
esac

echo "감지된 셸: $SHELL_NAME"
echo "대상 설정 파일: $RC_FILE"

# rc 파일이 없으면 생성 (디렉토리도 함께)
RC_DIR="$(dirname "$RC_FILE")"
if [ ! -d "$RC_DIR" ]; then
    mkdir -p "$RC_DIR"
fi
touch "$RC_FILE"

BEGIN_MARKER="# BEGIN AI CLI 기본 플래그 설정"
END_MARKER="# END AI CLI 기본 플래그 설정"

# 추가할 블록 정의
BLOCK=$(cat <<'EOF'
# BEGIN AI CLI 기본 플래그 설정
codex() {
    command codex --dangerously-bypass-approvals-and-sandbox "$@"
}

gemini() {
    command gemini --yolo "$@"
}

copilot() {
    command copilot --experimental --allow-all "$@"
}

grok() {
    command grok --yolo "$@"
}
# END AI CLI 기본 플래그 설정
EOF
)

# 기존 블록이 있는지 확인하고 교체 또는 추가
if grep -qF "$BEGIN_MARKER" "$RC_FILE"; then
    echo "기존 AI CLI 플래그 설정 블록을 발견했습니다. 갱신합니다..."
    # BEGIN ~ END 사이의 내용을 새 블록으로 교체 (BSD sed / GNU sed 호환)
    awk -v begin="$BEGIN_MARKER" -v end="$END_MARKER" -v block="$BLOCK" '
        BEGIN { in_block=0 }
        $0 ~ begin { in_block=1; print block; next }
        in_block && $0 ~ end { in_block=0; next }
        !in_block { print }
    ' "$RC_FILE" > "$RC_FILE.tmp" && mv "$RC_FILE.tmp" "$RC_FILE"
    echo "기존 블록을 새 설정으로 교체했습니다."
else
    echo "기존 블록이 없습니다. 파일 끝에 추가합니다..."
    # 파일 끝에 빈 줄 추가 후 블록 삽입
    if [ -s "$RC_FILE" ]; then
        # 파일이 비어있지 않으면 두 줄 개행 추가
        printf '\n\n' >> "$RC_FILE"
    fi
    printf '%s\n' "$BLOCK" >> "$RC_FILE"
    echo "설정 블록을 추가했습니다."
fi

echo ""
echo "✅ AI CLI 기본 플래그 설정이 $SHELL_NAME rc 파일에 적용되었습니다."
echo "설정 파일: $RC_FILE"
echo ""
echo "변경 사항을 현재 터미널 세션에 적용하려면 다음 명령을 실행하세요:"
echo "    source \"$RC_FILE\""
echo ""
echo "또는 새 터미널 창을 열어 주세요."
