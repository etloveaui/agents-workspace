# agents-workspace 프로젝트 설계

## 🎯 프로젝트 목표

전역 설치된 AI 도구들(Claude Code, Gemini CLI, Codex CLI)을 효율적으로 관리하고, 
필요한 최소한의 개인화만을 프로젝트에 포함하는 새로운 방식의 에이전트 워크스페이스.

## 📁 프로젝트 구조

```
C:\Users\eunta\agents-workspace\
├── README.md                    # 프로젝트 메인 가이드
├── PROJECT_DESIGN.md           # 이 파일 - 설계 문서
├── AGENTS.md                   # Codex 에이전트 지침
├── CLAUDE.md                   # Claude 에이전트 지침
├── GEMINI.md                   # Gemini 에이전트 지침
├── .gitignore                  # Git 제외 파일
├──
├── docs/                       # 문서화
│   ├── ai-tools-guide.md      # AI 도구별 사용 가이드
│   ├── project-rules.md       # 프로젝트 규칙
│   └── troubleshooting.md     # 문제 해결 가이드
│
├── configs/                    # 개인화 설정 (최소화)
│   ├── .vscode/               # VS Code 워크스페이스 설정
│   │   ├── settings.json      # 인코딩, 포맷 등
│   │   ├── tasks.json         # AI 도구 실행 Task
│   │   └── extensions.json    # 권장 확장
│   └── templates/             # 자주 사용하는 템플릿들
│
├── projects/                   # 개별 프로젝트들 (Git 제외)
│   ├── .gitkeep              # 빈 디렉토리 유지용
│   └── [각 프로젝트는 독립 Git 관리]
│
├── workspace/                  # 임시 작업 공간 (Git 제외)  
│   ├── drafts/               # 초안 작업들
│   ├── experiments/          # 실험적 코드들
│   └── temp/                 # 임시 파일들
│
└── archives/                   # 대화/작업 아카이브 (Git 관리)
    ├── conversations/         # 대화 기록들
    ├── work-sessions/         # 작업 세션 기록
    └── decisions/             # 주요 결정 사항들
```


## 🎯 설계 원칙

### 1. 전역 도구 활용
- Claude Code, Gemini CLI, Codex CLI는 모두 전역 설치
- 프로젝트는 설정만 관리, 도구 자체는 포함하지 않음
- 업데이트는 전역에서 관리

### 2. 최소한의 개인화
- 꼭 필요한 설정만 프로젝트에 포함
- VS Code 설정 (인코딩, 포맷 등)
- 자주 사용하는 템플릿들
- AI 도구 실행을 위한 Task 설정

### 3. 독립적 프로젝트 관리
- `projects/` 폴더: 각 프로젝트는 독립 Git
- 우리 메인 Git에서는 제외 (.gitignore)
- 프로젝트별로 필요한 AI 도구 선택 사용

### 4. 체계적 아카이빙
- 모든 대화와 작업을 기록
- 결정 사항과 학습 내용 보존
- Git으로 버전 관리

## 🔧 Git 관리 전략

### Git 관리 대상 (포함)
```
docs/                  # 문서들
configs/               # 설정 파일들  
archives/              # 대화/작업 기록
README.md              # 프로젝트 가이드
PROJECT_DESIGN.md      # 설계 문서
.gitignore             # Git 제외 설정
```

### Git 제외 대상
```
projects/              # 독립 Git 관리
workspace/             # 임시 작업 공간
*.log                  # 로그 파일들
.env                   # 환경 변수 (있다면)
```

## 🤖 AI 도구 통합 방식

### Claude Code
- 전역 설치: `npm install -g @anthropic-ai/claude-code`
- 설정 위치: `C:\Users\eunta\.claude\`
- 실행: VS Code Task 또는 `claude` 명령어

### Gemini CLI  
- 전역 설치 상태 유지
- 설정 위치: `C:\Users\eunta\.gemini\`
- 실행: VS Code Task 또는 `gemini` 명령어

### Codex CLI
- 전역 설치 상태 유지
- 실행: VS Code Task 또는 `codex` 명령어

## 📋 작업 규칙

### 새 프로젝트 시작
1. `projects/프로젝트명` 폴더 생성
2. 해당 폴더에서 `git init`
3. 필요한 AI 도구 선택하여 작업
4. 주요 결정사항은 `archives/decisions/` 기록

### 임시 작업
1. `workspace/` 폴더 활용
2. 실험적 코드나 초안 작업
3. 완료되면 적절한 위치로 이동

### 대화 아카이빙
1. 중요한 대화는 `archives/conversations/` 저장
2. 작업 세션은 `archives/work-sessions/` 저장
3. 월별로 정리

## 🎨 VS Code 통합

### 워크스페이스 설정
- 인코딩: UTF-8 강제
- 줄바꿈: LF 강제  
- 탭 크기: 2스페이스
- 자동 저장 등

### Task 설정
- Claude 실행: Ctrl+Shift+P → Run Task → Claude
- Gemini 실행: Ctrl+Shift+P → Run Task → Gemini  
- Codex 실행: Ctrl+Shift+P → Run Task → Codex

### 권장 확장
- AI 도구 관련 확장들
- 개발 효율성 확장들

## 🔄 확장 계획

### 단계별 구축
1. **Phase 1**: 기본 구조 + VS Code 설정
2. **Phase 2**: AI 도구 Task 통합
3. **Phase 3**: 템플릿 시스템
4. **Phase 4**: 아카이빙 자동화

### 유연한 확장
- 새로운 AI 도구 추가 시 configs/ 확장
- 프로젝트 요구사항에 따른 조정
- 사용 패턴에 따른 최적화

## 📈 성공 기준

1. **환경 독립성**: 다른 PC에서도 쉽게 복원 가능
2. **도구 독립성**: AI 도구 업데이트가 프로젝트에 영향 없음
3. **프로젝트 독립성**: 각 프로젝트가 독립적으로 관리됨
4. **효율성**: 필요한 설정만 포함하여 가벼움
5. **확장성**: 새로운 도구나 요구사항 쉽게 추가

이 설계는 fenok-multi-agent의 실패 원인을 반영하여:
- 복잡한 의존성 제거
- WSL2 종속성 제거  
- 최소한의 설정만 포함
- 명확한 책임 분리

를 통해 실용적이고 지속 가능한 워크스페이스를 목표합니다.