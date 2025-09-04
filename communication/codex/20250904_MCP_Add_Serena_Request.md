# MCP 추가 요청서 — Serena 등록 (for Claude)

요청자: Codex
날짜: 2025-09-04
대상 파일: `.mcp.json` (루트)
주의: 기존 항목/루트/정책은 변경하지 말 것. Serena만 추가.

## 배경
- 현재 등록된 MCP: filesystem, context7, sequential-thinking, playwright, hello-mcp, ide (`.mcp.json` 기준)
- 미등록: serena (코드 분석/메모리용 MCP)
- 로컬 설치 확인: `C:\\Users\\eunta\\.local\\bin\\serena-mcp-server.exe` 존재

## 작업 목표
`.mcp.json`에 `serena` 항목을 추가하여 Claude에서도 Serena MCP를 사용 가능하게 한다.

## 변경 사양(추가만, 수정 금지)
```json
{
  "mcpServers": {
    "serena": {
      "command": "node",
      "args": [
        "scripts/serena-launcher.js"
      ],
      "env": {}
    }
  }
}
```
- 이유: 실행 경로를 직접 하드코딩하지 않고, `scripts/serena-launcher.js`가 OS별 탐색(Windows: `%USERPROFILE%/.local/bin/serena-mcp-server.exe`, `%USERPROFILE%/.cargo/bin/...`)을 수행함.
- 다른 서버 설정(filesystem, context7, sequential-thinking, playwright, hello-mcp, ide)은 그대로 둘 것.
- `--root` 등 범위 설정은 `.mcp.json`의 기존 정책(`"--root", "."`) 유지.

## 작업 단계(권장)
1) 사전 확인
   - `node -v`, `npx -v` 정상
   - `C:\\Users\\eunta\\.local\\bin\\serena-mcp-server.exe` 존재 확인
2) Serena 항목 추가(위 JSON 스니펫을 `.mcp.json`에 병합)
3) 검증
   - 클라이언트에서 `tools/list` 실행 → `serena` 노출 확인
   - `serena --help` 또는 간단 호출(예: 상태 확인)이 정상
4) 문서화
   - `docs/QUICK_START.md`의 MCP 목록 라인에 `serena` 포함 여부 확인/업데이트(선택)

## 수용 기준(Acceptance Criteria)
- `tools/list`에 `serena`가 보인다.
- `serena` 호출 시 프로세스가 기동되고 에러 없이 응답한다.
- 기존 MCP 동작(filesystem 등)에 영향이 없다(루트/명령 미변경).

## 롤백
- `.mcp.json`에서 `serena` 섹션만 제거하면 됨(다른 항목은 그대로).

## 참고
- 자동 설정 스크립트: `npm run setup-mcp`는 Serena 바이너리를 찾을 경우 자동 등록 로직을 포함(`scripts/setup-mcp.js`). 수동 편집이 어렵다면 해당 스크립트 사용 가능(단, 다른 항목은 바꾸지 않도록 diff 확인 권장).

---
본 요청서는 “Serena 추가만”을 범위로 합니다. 다른 MCP, 루트, 승인 정책은 변경하지 말아 주세요.
