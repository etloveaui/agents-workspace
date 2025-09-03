# Quick Start

목표: 어떤 PC/사용자명/경로에서도 2–3분 내에 Codex/Claude/Gemini와 MCP를 바로 사용합니다.

---

## 1) 사전 준비(Prereqs)
- Node.js 20+ (권장 22+)
- VS Code(선택) 또는 터미널
- Windows: PowerShell 실행 정책 허용(Benefit: 자동 신뢰 스크립트 실행)

---

## 2) 클론 및 열기
```bash
# 원하는 폴더에서
git clone <your-repo-url> agents-workspace
cd agents-workspace

# VS Code로 열기(권장)
code .
```

- VS Code를 열면 자동 태스크가 실행되어 신뢰 경로가 설정됩니다.
  - 자동 태스크: 
    - `.vscode/tasks.json`의 "SuperCodex: ensure trust"
    - 실행 스크립트: `scripts/ensure-trust.ps1`
  - 보안 팝업이 뜨면 Allow를 눌러주세요.

수동 실행(자동 태스크 대신)
```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts/ensure-trust.ps1
```

---

## 3) 실행(Clients)
- Codex: 터미널에서 `codex`
- Claude Code: IDE 통합 실행(프로젝트 루트에서)
- Gemini CLI: `gemini`

참고: 승인/샌드박스는 프로젝트 설정(`.codex/config.toml`)을 따릅니다.

---

## 4) MCP 동작 확인(필수 체크)
클라이언트(예: Codex/Claude/Gemini)에서 다음을 시도하세요.
- tools/list → hello-mcp, filesystem, sequential-thinking, context7, playwright, serena(옵션) 확인
- tools/call →
  - name: `echo`, arguments: `{ "text": "안녕하세요" }`
  - name: `time`
- filesystem →
  - roots/list: 프로젝트 루트(`.`), `.claude`, `.gemini` 노출 확인
  - resources/list, resources/read: 예: README.md 읽기

---

## 5) 경로/신뢰 구성 원리
- 경로: `.mcp.json`, `.codex/config.toml`, `.gemini/settings.json`은 상대 경로(`.`, `.claude`, `.gemini`)로 구성되어 어떤 사용자명에도 안전합니다.
- 신뢰: 첫 실행 시 `scripts/ensure-trust.ps1`가 현재 PC의 절대경로를 `.codex/config.toml`과 `.gemini/trustedFolders.json`에 자동 주입합니다.

---

## 6) 문제 해결(Troubleshooting)
- 승인 팝업이 자주 뜸 → 현재 세션의 런타임 정책이 설정을 덮을 수 있습니다. 세션 재시작 필요.
- 파일 접근 불가 → MCP filesystem roots가 상대 경로로 유지되는지 확인(`.`, `.claude`, `.gemini`).
- Windows/WSL 경로 이슈 → `C:\` ↔ `/mnt/c` 매핑 확인.
- Serena 경로 문제 → `.mcp.json`의 `serena` 실행 경로를 PATH 기반으로 변경하거나 비활성화(원하시면 패치 지원).

---

## 7) 다음 단계(옵션)
- macOS/Linux 자동화: `scripts/ensure-trust.sh` 추가 및 VS Code OS별 자동 태스크 구성 가능.
- 워크플로 문서화 보강: docs/WORKLOG_YYYY-MM-DD.md, docs/CODEX_CLI_SUMMARY.md 확인.
- 커스텀 MCP 확장: `servers/hello-mcp/`에 파일/HTTP 유틸 툴 추가 가능.

