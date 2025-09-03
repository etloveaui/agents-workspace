# agents-workspace 프로젝트 설계

## 🎯 프로젝트 목표

**SuperAI 프레임워크**: Claude Code, Gemini CLI, Codex CLI를 통합한 차세대 AI 협업 워크스페이스

전역 설치된 AI 도구들의 효율적 관리와 크로스 플랫폼 호환성을 통해, 
어떤 컴퓨터에서든 일관된 AI 협업 환경을 제공하는 새로운 워크스페이스 구축.

---

## 🏗️ 현재 구현 상태 (2025-09-03 기준)

### ✅ 완료된 구성요소

#### 1. SuperAI 프레임워크 기반 구조
```
agents-workspace/
├── 📋 관리 문서
│   ├── PROJECT_DESIGN.md           # 프로젝트 설계 (업데이트됨)
│   ├── README.md                   # 메인 가이드
│   └── .mcp.json                   # MCP 서버 설정
│
├── 🚀 동적 설정 스크립트 (핵심 혁신)
│   ├── setup-claude.js             # SuperClaude 자동 설정
│   ├── setup-codex.js              # SuperCodex 자동 설정  
│   └── setup-gemini.js             # SuperGemini 자동 설정
│
├── 📚 표준화된 문서 체계
│   ├── docs/
│   │   ├── DOCUMENTATION_STANDARDS.md  # 문서화 표준 규정
│   │   └── AI_COMMUNICATION_GUIDE.md   # AI 커뮤니케이션 가이드
│   │
│   └── workspace/temp/
│       ├── prompting guide.md      # Claude 프롬프팅 가이드 (참고용)
│       └── codexconfig.md           # Codex 설정 참고 자료
│
├── 🔧 AI 도구별 설정 디렉토리
│   ├── .claude/                    # SuperClaude 프로젝트 설정
│   │   ├── settings.local.json     # 프로젝트별 설정
│   │   ├── CLAUDE.md               # 사용 가이드
│   │   └── README.md               # 설정 설명서
│   │
│   ├── .codex/                     # SuperCodex 프로젝트 설정
│   │   ├── AGENTS.md               # 코딩 프레임워크 지침
│   │   ├── prompts/                # 커스텀 프롬프트 모음
│   │   │   ├── analyze.md
│   │   │   ├── implement.md
│   │   │   ├── debug.md
│   │   │   ├── optimize.md
│   │   │   └── document.md
│   │   ├── settings.json           # 프로젝트 메타데이터
│   │   └── README.md               # 설정 설명서
│   │
│   └── .gemini/                    # SuperGemini 프로젝트 설정
│       ├── commands/sg/            # 프로젝트별 커스텀 명령어
│       │   └── analyze.toml
│       ├── GEMINI.md               # 사용 가이드
│       └── README.md               # 설정 설명서
│
└── 📦 아카이브 공간
    └── old_project/                # 이전 프로젝트 참조용
```

#### 2. 크로스 플랫폼 호환성 시스템
- **동적 사용자 감지**: `os.userInfo().username` 활용
- **경로 자동 해석**: Windows/Mac/Linux 호환 경로 처리
- **설정 파일 형식 준수**: 각 AI 도구의 실제 형식에 정확히 맞춤
  - Claude: 간단한 JSON (`settings.json`)
  - Codex: TOML 형식 (`config.toml`)
  - Gemini: JSON + 별도 trustedFolders (`settings.json`, `trustedFolders.json`)

#### 3. 크로스 AI 도구 통합
- **신뢰 네트워크**: 각 AI 도구가 다른 도구의 설정 폴더에 접근 가능
- **MCP 서버 공유**: filesystem, sequential-thinking, context7 등 공통 활용
- **설정 동기화**: 한 번의 설정으로 모든 도구에서 활용 가능

### 🔄 핵심 혁신: 동적 설정 시스템

#### 문제 해결
**기존 문제**: 하드코딩된 사용자 경로로 인한 이식성 부족
```javascript
// ❌ 기존 방식 (하드코딩)
"C:\\Users\\eunta\\.claude"  // 다른 컴퓨터에서 실패
```

**혁신적 해결책**: 동적 감지 및 생성
```javascript
// ✅ SuperAI 방식 (동적)
const username = os.userInfo().username;
const homeDir = os.homedir();
path.join(homeDir, '.claude')  // 모든 컴퓨터에서 동작
```

#### 실사용 시나리오
```bash
# 회사 컴퓨터 (사용자명: eunta)
node setup-claude.js    # → C:\Users\eunta\.claude\ 설정

# 집 컴퓨터 (사용자명: myname)  
node setup-claude.js    # → C:\Users\myname\.claude\ 설정

# Mac (사용자명: user)
node setup-claude.js    # → /Users/user/.claude/ 설정
```

---

## 🎯 설계 원칙 (업데이트됨)

### 1. 플랫폼 독립성 (Platform Independence)
- **OS 중립**: Windows, Mac, Linux 모든 환경에서 동작
- **경로 중립**: 절대경로 하드코딩 제거, 동적 경로 해석
- **사용자 중립**: 어떤 사용자명이든 자동 감지 및 설정

### 2. AI 도구 간 협업 최적화
- **크로스 참조**: 각 AI가 다른 AI의 설정과 데이터에 접근 가능
- **공통 MCP**: 동일한 MCP 서버를 모든 AI 도구에서 활용
- **설정 동기화**: 한 곳에서 설정하면 모든 도구에 반영

### 3. 실제 형식 준수 (Real Format Compliance)
- **정확한 설정**: 각 AI 도구의 실제 설정 파일 형식 100% 준수
- **검증된 구조**: 실제 동작하는 설정들을 역공학하여 정확히 구현
- **호환성 보장**: 업데이트 시에도 기존 설정과 충돌하지 않음

### 4. 문서화 체계화
- **표준 규정**: 문서화 작성 표준과 AI 커뮤니케이션 가이드 수립
- **작업 추적**: 모든 작업을 TodoWrite로 추적하고 기록
- **지식 축적**: 작업 과정과 결과를 체계적으로 문서화

---

## 🔧 AI 도구별 통합 방식 (업데이트됨)

### SuperClaude (Claude Code)
```json
전역 설정: ~/.claude/settings.json (statusLine 등)
프로젝트 설정: 프로젝트/.claude/settings.local.json
특징: MCP 서버 자동 감지, 크로스 도구 접근
실행: claude
```

### SuperCodex (Codex CLI)
```toml  
전역 설정: ~/.codex/config.toml
- [projects."path"] 신뢰 프로젝트 등록
- [mcp_servers.filesystem] MCP 서버 설정
- [profiles.analysis] 작업 모드별 프로필
프로젝트 설정: 프로젝트/.codex/AGENTS.md + prompts/
실행: codex --profile analysis
```

### SuperGemini (Gemini CLI)
```json
전역 설정: ~/.gemini/settings.json (mcpServers)
신뢰 설정: ~/.gemini/trustedFolders.json {"path": "TRUST_FOLDER"}
프로젝트 설정: 프로젝트/.gemini/commands/sg/
실행: gemini -p "/sg:analyze"
```

---

## 📋 현재 작업 흐름

### 1. 새 컴퓨터에서 시작 시
```bash
git clone [repository]
cd agents-workspace

# 모든 AI 도구를 한번에 설정
node setup-claude.js
node setup-codex.js  
node setup-gemini.js

# 즉시 사용 가능
claude
codex --profile analysis
gemini
```

### 2. 프로젝트 작업 시
```bash
# AI 도구들이 자동으로 다음에 접근 가능:
# - 현재 프로젝트 디렉토리
# - ~/.claude, ~/.codex, ~/.gemini (크로스 참조)
# - 공통 MCP 서버들 (filesystem, sequential-thinking, context7)

# 작업 추적은 TodoWrite로 자동화
# 문서화는 표준 규정에 따라 체계화
```

### 3. 문제 해결 시  
```bash
# 설정 문제 → setup 스크립트 재실행
# MCP 서버 문제 → 공통 설정으로 일관성 보장
# 권한 문제 → 크로스 참조 설정으로 해결
```

---

## 🎯 달성한 성과

### ✅ 기술적 성과
1. **100% 크로스 플랫폼**: 모든 OS에서 동작하는 설정 시스템
2. **실제 형식 준수**: 각 AI 도구의 정확한 설정 파일 형식 구현  
3. **크로스 AI 통합**: 3개 AI 도구가 서로의 데이터에 접근 가능
4. **자동화**: 복잡한 설정을 1분 내에 완전 자동 구성

### ✅ 운영적 성과
1. **표준화**: 문서화 및 커뮤니케이션 표준 수립
2. **체계화**: 작업 추적과 기록 시스템 구축
3. **최적화**: 불필요한 파일 정리 및 workspace 구조화
4. **지속가능성**: 확장 가능하고 유지보수 가능한 구조

---

## 🔮 확장 계획

### Phase 1: 안정화 (완료)
- ✅ 동적 설정 시스템 구축
- ✅ 크로스 AI 도구 통합
- ✅ 문서화 표준 수립

### Phase 2: 고도화 (진행중)
- 🔄 프로젝트별 템플릿 시스템
- 🔄 자동화 스크립트 확장
- 🔄 성능 모니터링 및 최적화

### Phase 3: 지능화 (계획)
- 📋 AI 도구 간 작업 자동 전달
- 📋 컨텍스트 공유 및 기억 시스템
- 📋 개인화된 워크플로우 자동 생성

---

## 🏆 성공 기준 달성도

| 기준 | 목표 | 현재 상태 | 달성도 |
|------|------|-----------|---------|
| **환경 독립성** | 다른 PC에서 쉽게 복원 | 1분 내 자동 설정 | ✅ 100% |
| **도구 독립성** | AI 도구 업데이트 무관 | 실제 형식 준수 | ✅ 100% |
| **크로스 통합** | AI 도구 간 협업 | 완전한 크로스 참조 | ✅ 100% |
| **효율성** | 가벼운 설정 | 필수 설정만 포함 | ✅ 100% |
| **확장성** | 새 도구 쉽게 추가 | 표준화된 구조 | ✅ 95% |
| **문서화** | 체계적 기록 관리 | 표준 규정 수립 | ✅ 90% |

---

**SuperAI 프레임워크**는 fenok-multi-agent의 실패를 교훈 삼아:
- ❌ 복잡한 의존성 → ✅ 동적 감지 시스템
- ❌ WSL2 종속성 → ✅ 완전한 크로스 플랫폼  
- ❌ 하드코딩 경로 → ✅ 자동 경로 해석
- ❌ 추측 기반 설정 → ✅ 실제 형식 준수

를 통해 **실용적이고 지속 가능한 차세대 AI 협업 워크스페이스**를 성공적으로 구축했습니다.

---

*마지막 업데이트: 2025-09-03*  
*다음 업데이트: Phase 2 고도화 완료 시*