# [LLM INTRODUCTORY REPORT – FENOMENO]

## Executive Summary
- FENOMENO는 **투자 전략**, **임베디드 엔지니어링**, **AI 멀티에이전트 자동화**를 동시에 다루는 복합형 전문가.  
- 레버리지 ETF 기반 고위험 성장 포트폴리오 운용과 저레벨 임베디드 개발 경험을 보유.  
- **TerminalX**, **100xFenok** 등 LLM·CLI 기반 툴체인을 직접 설계·구축하며, 멀티모델 환경을 운영.  
- 주요 성과는 투자 대시보드 자동화, MCAL 모듈 개발, LLM CLI 생태계 정립.  
- 비전은 LLM/CLI와의 협업을 통해 **투자+기술 융합형 전략가**로 확장.  

---

## Identity & Background
- **정체성**: AI 기반 투자 전략가, 자동차 임베디드 소프트웨어 개발자.  
- **배경**:  
  - 금융 영역에서 레버리지 ETF를 기반으로 한 포트폴리오 관리와 섹터별 AI 스크리닝 경험.  
  - 엔지니어링 영역에서 Infineon TC364, AUTOSAR MCAL 기반 저레벨 모듈 설계·구현.  
  - CLI와 LLM을 활용하여 **코드 실행-데이터 분석-리포트 생성**이 하나의 파이프라인으로 연결되는 자동화 환경을 구축.  

---

## Core Competencies
- **투자 전략**  
  - 레버리지 ETF (FNGB, NVDL, PTIR, AVGX 등) 중심 포트폴리오 관리.  
  - Core-Satellite, Infinite Buying, Value Rebalancing 전략을 체계적으로 적용.  
  - AI 스크리닝을 통한 섹터별 차별화 투자 전략 개발.  

- **엔지니어링**  
  - TC364 및 AUTOSAR MCAL 기반 저레벨 드라이버 구현 (SPI, ADC, DAC 모듈).  
  - Tasking 빌드 환경을 VS Code/CLI 기반으로 전환, 자동화된 빌드·테스트 파이프라인 구축.  
  - PowerShell, WSL, Makefile, 링커 스크립트를 활용한 멀티플랫폼 빌드 환경 최적화.  

- **AI/LLM 활용**  
  - **TerminalX**: LLM 프롬프트 오케스트레이션 시스템. (섹터별 스크리닝, PDF 호환 리포트 생성, 멀티모델 호출 자동화)  
  - **100xFenok**: HTML+Tailwind 기반 투자 대시보드 (Stooq, AlphaVantage API 연동, SPA 구조).  
  - **멀티모델 CLI 통합**: Codex CLI, Gemini CLI, SuperClaude를 포함한 멀티에이전트 CLI 환경 구축.  

---

## Unique Differentiators
- **멀티도메인 연결성**: 금융 데이터 해석과 저레벨 코드 작성 모두 가능.  
- **LLM/CLI 친화적 설계자**: 데이터·코드·리포트를 CLI-에이전트 구조에 맞게 재편.  
- **자동화 지향**: 반복적인 금융 계산, 빌드 테스트, 데이터 변환 작업을 LLM과 CLI로 치환.  
- **전략-실행 결합**: 투자 전략을 단순 모델링이 아닌, 대시보드/스크리닝 코드/보고서로 즉시 변환.  

---

## Achievements & Impact
- **투자 영역**  
  - 고위험 성장 포트폴리오를 직접 운용하여 레버리지 ETF의 전략적 사용을 정립.  
  - TerminalX 기반 섹터별 AI 스크리닝 프롬프트 작성으로 **PDF 친화 리포트 자동화** 구현.  

- **엔지니어링 영역**  
  - SPI 기반 DAC 드라이버(TLV5614, DAC8803) 및 ADC 듀얼 샘플링 알고리즘 개발.  
  - Tasking 전용 빌드 환경을 VS Code CLI 기반으로 이식, 개발 생산성 향상.  

- **AI/CLI 프로젝트**  
  - **TerminalX**: 멀티LLM 기반 리서치 프레임워크 (Executive Summary → Methodology → Tables → Catalysts 구조).  
  - **100xFenok**: GitHub Actions로 구동되는 실시간 데이터 대시보드 자동화.  
  - **CLI 통합 환경**: Codex, Gemini, Claude 등 LLM을 CLI에서 병렬 호출·실험할 수 있는 인프라 구축.  

---

## Collaboration Potential with LLMs
- **CLI 친화적 협업**  
  - LLM이 CLI로 실행되는 환경에서 즉시 적용 가능한 입력·출력 구조 보유.  
  - 예: `cx`(Codex), `gem`(Gemini), `sc`(SuperClaude) 같은 alias 기반 CLI 호출 체계에 맞는 프롬프트 최적화.  

- **데이터 파이프라인 자동화**  
  - 투자 데이터 스크래핑 → 변환 → 대시보드화 → 리포트 생성까지 LLM이 각 단계에서 지원 가능.  
  - CLI에서 JSON/CSV를 생성하고 곧바로 Markdown 리포트나 HTML 차트로 변환.  

- **코드 리뷰·테스트**  
  - 임베디드 코드의 컴파일/링커 오류를 LLM CLI가 즉시 분석하고 수정 제안.  
  - CLI 빌드 로그를 입력값으로 주면, 에러 발생 지점과 수정 코드까지 자동 출력.  

- **멀티에이전트 오케스트레이션**  
  - LLM들이 역할을 나눠 동시에 작업:  
    - Agent A: 데이터 수집/정규화  
    - Agent B: 분석/통계 처리  
    - Agent C: 리포트 작성/시각화  
  - CLI 기반 환경에서 병렬 실행 및 조율 가능.  

---

## Conclusion & Outlook
- FENOMENO는 투자·엔지니어링·AI 자동화를 융합한 드문 프로파일.  
- LLM과 CLI는 **데이터 처리, 코드 검증, 리포트 자동화**에서 FENOMENO의 역량을 증폭할 수 있음.  
- 향후 방향:  
  1. 투자-기술 융합 리포트의 **완전 자동화**  
  2. 임베디드 코드와 금융 데이터 모두를 처리하는 **양방향 LLM CLI 생태계** 확립  
  3. 장기적으로는 **멀티에이전트 기반 의사결정 플랫폼** 구축  

결론적으로, FENOMENO는 LLM/CLI 협업 환경에서 **전략 수립 → 코드 구현 → 자동화 리포트 생성**까지 연결할 수 있는 핵심 파트너로 작동할 수 있다.  
