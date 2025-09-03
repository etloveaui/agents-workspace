# MCP Configuration Management

이 프로젝트는 환경 변화에 유연하게 대응할 수 있는 MCP (Model Context Protocol) 설정을 제공합니다.

## 자동 설정

```bash
# MCP 서버 설정 자동 생성
npm run setup-mcp

# 사용 가능한 MCP 서버 확인
npm run check-mcp
```

## 환경별 MCP 서버 대응

### 기본 서버 (항상 사용 가능)
- **filesystem**: 파일 시스템 접근
- **context7**: 문서 검색 및 컨텍스트
- **sequential-thinking**: 순차적 사고 분석
- **playwright**: 브라우저 자동화
- **hello-mcp**: 테스트용 에코 서버
- **ide**: IDE 통합

### 선택적 서버 (환경에 따라)
- **serena**: 코드 분석 및 메모리 (Rust 바이너리 필요)

## 환경 이전 시

새로운 환경으로 이전할 때는 단순히 다음 명령어만 실행하면 됩니다:

```bash
npm run setup-mcp
```

이 스크립트는 자동으로:
1. 현재 환경에서 사용 가능한 MCP 서버를 감지
2. 적절한 `.mcp.json` 설정 파일 생성
3. 하드코딩된 경로 없이 동적으로 구성

## 수동 설정

특별한 요구사항이 있는 경우, `.mcp.json`을 직접 수정할 수 있지만 
`npm run setup-mcp`를 실행하면 자동으로 덮어써집니다.

## 문제 해결

MCP 서버가 작동하지 않는 경우:

1. 서버 가용성 확인: `npm run check-mcp`
2. 설정 재생성: `npm run setup-mcp`
3. 개별 서버 테스트: `npx -y [server-name] --help`