# SuperGemini 프로젝트 설정

이 폴더는 **agents-workspace** 프로젝트의 Gemini 설정을 담고 있습니다.

## 설정 파일들
- `settings.json`: 프로젝트별 Gemini 설정 및 MCP 서버
- `GEMINI.md`: 프로젝트 특화 지침
- `commands/sg/`: 프로젝트별 커스텀 명령어들

## 자동 설정된 신뢰 폴더
- C:\Users\eunta\multi-agent-workspace
- C:\Users\eunta
- C:\Users\eunta\agents-workspace
- C:\Users\eunta\.claude
- C:\Users\eunta\.codex

## 사용법
```bash
gemini                    # 대화형 모드
gemini -p "/sg:analyze"   # 프로젝트 분석
```

## 다른 컴퓨터에서 사용
```bash
node setup-gemini.js     # 자동으로 사용자명에 맞게 재설정
```
