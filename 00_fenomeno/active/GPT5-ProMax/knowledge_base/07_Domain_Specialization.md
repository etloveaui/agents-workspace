# 도메인별 특화 패턴 가이드

## 🎯 도메인 특화 프롬프팅 철학

각 전문 분야는 고유한 사고 패턴, 용어체계, 평가 기준을 가지고 있습니다. GPT5의 강력한 적응 능력을 활용하여 각 도메인의 전문성을 최대한 끌어내는 특화된 프롬프트 패턴을 제공합니다.

## 💼 비즈니스 & 경영 도메인

### 전략 컨설팅 패턴
```markdown
# 전략 컨설팅 프롬프트 패턴

## 🎯 컨설팅 미션
[클라이언트 상황과 해결하고자 하는 전략적 과제]

## 📊 McKinsey 스타일 분석 프레임워크
다음 구조를 따라 체계적인 전략 분석을 수행해주세요:

### 1. Situation Analysis (상황 분석)
- **Context**: 산업 환경과 비즈니스 맥락
- **Challenge**: 직면한 핵심 도전과제
- **Constraints**: 제약 조건과 전제사항

### 2. MECE 이슈 분해
주요 전략 이슈를 상호 배타적이고 총체적으로 분해:
- **Market Issues**: 시장 관련 이슈들
- **Operational Issues**: 운영 관련 이슈들  
- **Financial Issues**: 재무 관련 이슈들
- **Organizational Issues**: 조직 관련 이슈들

### 3. Hypothesis-Driven Analysis
각 이슈에 대한 가설 수립과 검증:
- **Primary Hypothesis**: 주요 가설
- **Supporting Evidence**: 뒷받침 근거
- **Counter Evidence**: 반박 근거
- **Confidence Level**: 확신 수준 (Low/Medium/High)

## 🎯 Strategic Recommendations
- **So What?**: 분석 결과의 전략적 함의
- **Action Plan**: 구체적 실행 방안
- **Success Metrics**: 성공 측정 지표
- **Risk Mitigation**: 리스크 완화 방안

## ⚡ GPT5 최적화
"Think like a senior strategy consultant and provide McKinsey-quality analysis with clear recommendations"
```

### 벤처 투자 심사 패턴
```markdown
# VC 투자 심사 프롬프트 패턴

## 💰 투자 검토 대상
[회사명, 업종, 투자 라운드, 요청 투자 금액]

## 📊 VC 듀딜리전스 프레임워크
다음 관점에서 투자 매력도를 평가해주세요:

### 1. Market Analysis (시장 분석)
- **TAM/SAM/SOM**: 시장 규모 및 접근 가능성
- **Market Growth**: 시장 성장률과 성장 동력
- **Market Timing**: 시장 진입 타이밍의 적절성
- **Competitive Landscape**: 경쟁 환경과 포지셔닝

### 2. Business Model & Traction (사업 모델 및 견인력)
- **Value Proposition**: 고객 가치 제안의 명확성
- **Revenue Model**: 수익 모델의 지속가능성
- **Unit Economics**: 단위 경제학과 수익성
- **Growth Metrics**: 성장 지표와 트렌드

### 3. Team Assessment (팀 평가)
- **Founder-Market Fit**: 창업자와 시장 간 적합성
- **Team Composition**: 팀 구성의 균형과 역량
- **Execution Track Record**: 실행 경험과 성과
- **Vision & Leadership**: 비전과 리더십 역량

### 4. Product & Technology (제품 및 기술)
- **Product-Market Fit**: 제품-시장 적합성
- **Technical Differentiation**: 기술적 차별화
- **Scalability**: 확장성과 기술 아키텍처
- **IP & Moats**: 지적재산권과 경쟁 우위

## 💎 Investment Decision Framework
- **Investment Grade**: A/B/C/D (근거 포함)
- **Valuation Range**: 적정 기업 가치 범위
- **Key Risks**: 주요 투자 리스크 3가지
- **Value Creation Plan**: 투자 후 가치 창출 방안

## ⚡ GPT5 최적화
"Analyze this investment opportunity with the rigor of a tier-1 VC partner"
```

## 💻 기술 & 개발 도메인

### 시스템 아키텍처 설계 패턴
```markdown
# 시스템 아키텍처 설계 프롬프트 패턴

## 🏗️ 아키텍처 설계 요구사항
[시스템 목적, 예상 규모, 성능 요구사항, 제약사항]

## 📐 Architecture Design Process
다음 단계에 따라 체계적으로 시스템을 설계해주세요:

### 1. Requirements Analysis
- **Functional Requirements**: 기능적 요구사항
- **Non-Functional Requirements**: 
  - Performance: QPS, Latency, Throughput
  - Scalability: Horizontal/Vertical scaling needs
  - Reliability: Availability, Fault tolerance
  - Security: Authentication, Authorization, Data protection
  - Maintainability: Monitoring, Logging, Debugging

### 2. High-Level Architecture
- **System Components**: 주요 컴포넌트와 역할
- **Data Flow**: 데이터 흐름도
- **Technology Stack**: 권장 기술 스택과 선택 근거
- **Deployment Architecture**: 배포 아키텍처

### 3. Detailed Design
#### API Design
- **REST/GraphQL**: API 스타일 선택과 근거
- **Endpoint Design**: 주요 엔드포인트 명세
- **Request/Response Format**: 데이터 형식
- **Error Handling**: 에러 처리 전략

#### Database Design  
- **Data Model**: 엔티티 관계도
- **Database Selection**: SQL vs NoSQL 선택 근거
- **Partitioning Strategy**: 데이터 분산 전략
- **Caching Strategy**: 캐싱 계층 설계

#### Security Architecture
- **Authentication Flow**: 인증 방식
- **Authorization Model**: 권한 관리
- **Data Encryption**: 암호화 전략
- **Security Boundaries**: 보안 경계 설정

## 🔧 Implementation Considerations
- **Scalability Planning**: 확장성 대비책
- **Monitoring & Alerting**: 모니터링 전략
- **CI/CD Pipeline**: 배포 파이프라인
- **Disaster Recovery**: 재해 복구 계획

## ⚡ GPT5 최적화
"Design a robust, scalable system architecture following industry best practices and considering all technical constraints"
```

### 코드 리뷰 & 최적화 패턴
```markdown
# 코드 리뷰 최적화 프롬프트 패턴

## 💻 코드 리뷰 대상
[프로그래밍 언어, 코드 블록 또는 파일, 컨텍스트]

## 🔍 전문가급 코드 리뷰 프레임워크
다음 관점에서 종합적인 코드 분석을 수행해주세요:

### 1. Code Quality Assessment
#### Readability & Maintainability
- **Naming Conventions**: 변수, 함수, 클래스명의 명확성
- **Code Structure**: 논리적 구조와 흐름
- **Comments & Documentation**: 주석의 적절성과 완성도
- **Code Duplication**: 중복 코드 식별과 개선 방안

#### SOLID Principles Compliance
- **S**ingle Responsibility: 단일 책임 원칙 준수
- **O**pen/Closed: 개방-폐쇄 원칙 적용
- **L**iskov Substitution: 리스코프 치환 원칙
- **I**nterface Segregation: 인터페이스 분리 원칙
- **D**ependency Inversion: 의존 역전 원칙

### 2. Performance Analysis
- **Time Complexity**: 알고리즘 시간 복잡도
- **Space Complexity**: 메모리 사용 효율성
- **Bottleneck Identification**: 성능 병목 지점
- **Optimization Opportunities**: 최적화 가능 영역

### 3. Security Review
- **Input Validation**: 입력 검증 충분성
- **SQL Injection**: SQL 인젝션 취약점
- **XSS Prevention**: 크로스사이트 스크립팅 대비
- **Authentication/Authorization**: 인증/권한 처리

### 4. Best Practices Adherence
- **Language-Specific**: 언어별 베스트 프랙티스
- **Framework Patterns**: 프레임워크 권장 패턴
- **Error Handling**: 예외 처리 방식
- **Logging Strategy**: 로깅 전략

## 🎯 개선 권고사항
각 문제점에 대해:
- **Severity Level**: Critical/High/Medium/Low
- **Specific Fix**: 구체적 수정 방안
- **Code Example**: 개선된 코드 예시
- **Priority**: 수정 우선순위

## ⚡ GPT5 최적화  
"Conduct thorough code review with senior developer expertise, focusing on quality, performance, and maintainability"
```

## 📊 데이터 & 분석 도메인

### 데이터 사이언스 프로젝트 패턴
```markdown
# 데이터 사이언스 프로젝트 프롬프트 패턴

## 🔬 프로젝트 정의
[비즈니스 문제, 데이터 현황, 예상 결과물]

## 📈 End-to-End ML Project Framework
CRISP-DM 방법론을 따라 체계적 접근:

### 1. Business Understanding
- **Business Objective**: 해결하고자 하는 비즈니스 문제
- **Success Criteria**: 성공 측정 기준
- **Project Plan**: 프로젝트 일정과 리소스
- **Risk Assessment**: 프로젝트 리스크 요인

### 2. Data Understanding  
- **Data Collection**: 필요한 데이터 소스 식별
- **Data Description**: 데이터 특성과 구조 분석
- **Data Quality**: 데이터 품질 이슈 식별
- **Initial Insights**: 초기 데이터 탐색 결과

### 3. Data Preparation
- **Data Cleaning**: 결측치, 이상치 처리 전략
- **Feature Engineering**: 특성 생성 및 변환
- **Data Integration**: 다중 소스 데이터 통합
- **Data Splitting**: 훈련/검증/테스트 세트 분할

### 4. Modeling
- **Algorithm Selection**: 문제 유형별 알고리즘 후보
- **Model Training**: 훈련 전략과 하이퍼파라미터
- **Cross-Validation**: 모델 검증 방법
- **Ensemble Methods**: 앙상블 기법 적용

### 5. Evaluation
- **Metrics Selection**: 평가 지표 선택 근거
- **Model Performance**: 성능 평가 결과
- **Business Impact**: 비즈니스 관점 평가
- **Model Interpretation**: 모델 해석과 설명

### 6. Deployment
- **Production Architecture**: 배포 아키텍처 설계
- **Monitoring Strategy**: 모델 성능 모니터링
- **Maintenance Plan**: 모델 유지보수 계획
- **Rollback Plan**: 문제 발생 시 대응 방안

## 🎯 실행 로드맵
각 단계별 구체적 작업:
- **Timeline**: 예상 소요 시간
- **Deliverables**: 단계별 산출물
- **Dependencies**: 의존 관계
- **Quality Gates**: 단계별 품질 검증 기준

## ⚡ GPT5 최적화
"Approach this as a senior data scientist with deep ML expertise and business acumen"
```

## 🎨 마케팅 & 창작 도메인

### 브랜드 마케팅 전략 패턴
```markdown
# 브랜드 마케팅 전략 프롬프트 패턴

## 🎯 브랜드 마케팅 미션
[브랜드명, 산업, 타겟 시장, 마케팅 목표]

## 🧠 Strategic Brand Framework
다음 프레임워크로 종합적 브랜드 전략을 수립해주세요:

### 1. Brand Situation Analysis
#### Market Context
- **Industry Landscape**: 산업 환경과 트렌드
- **Competitive Analysis**: 주요 경쟁자 브랜드 전략
- **Market Opportunity**: 시장 기회와 위협 요소
- **Consumer Behavior**: 소비자 행동 변화 패턴

#### Brand Audit
- **Brand Equity**: 현재 브랜드 자산 평가
- **Perception Gap**: 인식과 현실 간 차이
- **Touchpoint Analysis**: 고객 접점별 브랜드 경험
- **Brand Architecture**: 브랜드 포트폴리오 구조

### 2. Strategic Brand Positioning
- **Target Audience**: 핵심 타겟 고객 정의
- **Brand Promise**: 브랜드 약속과 가치 제안
- **Differentiation**: 차별화 포인트
- **Brand Personality**: 브랜드 성격과 개성

### 3. Integrated Marketing Mix
#### Creative Strategy
- **Big Idea**: 핵심 크리에이티브 아이디어
- **Key Messages**: 주요 메시지 계층
- **Tone & Manner**: 커뮤니케이션 톤앤매너
- **Creative Execution**: 크리에이티브 실행 방향

#### Media Strategy
- **Channel Mix**: 최적 미디어 믹스
- **Content Strategy**: 채널별 콘텐츠 전략
- **Campaign Timeline**: 캠페인 실행 일정
- **Budget Allocation**: 예산 배분 전략

### 4. Performance Measurement
- **Brand KPIs**: 브랜드 성과 지표
- **Attribution Model**: 기여도 측정 모델
- **ROI Analysis**: 투자 대비 효과 분석
- **Optimization Plan**: 지속 개선 계획

## 🚀 90일 실행 계획
- **Phase 1 (0-30일)**: 런칭 준비
- **Phase 2 (31-60일)**: 본격 실행  
- **Phase 3 (61-90일)**: 최적화 및 확산

## ⚡ GPT5 최적화
"Think like a creative strategist at a top advertising agency with deep brand marketing expertise"
```

### 콘텐츠 크리에이션 패턴
```markdown
# 콘텐츠 크리에이션 프롬프트 패턴

## ✍️ 콘텐츠 제작 브리프
[콘텐츠 유형, 타겟 오디언스, 목적, 채널, 분량]

## 🎨 크리에이티브 콘텐츠 프로세스

### 1. Audience Research & Insights
- **Persona Development**: 상세한 타겟 페르소나
- **Pain Points**: 오디언스의 주요 고민과 니즈
- **Content Preferences**: 선호하는 콘텐츠 형태와 스타일
- **Engagement Patterns**: 참여 행동과 소비 패턴

### 2. Content Strategy Framework
#### Content Pillars (콘텐츠 기둥)
- **Educational**: 교육적 가치 제공
- **Inspirational**: 영감과 동기 부여
- **Entertainment**: 재미와 즐거움 제공
- **Behind-the-scenes**: 브랜드 스토리와 진정성

#### Storytelling Structure
- **Hook**: 첫 3초 내 관심 끌기
- **Context**: 배경과 상황 설정
- **Conflict**: 갈등이나 문제 제시
- **Resolution**: 해결책이나 결론
- **Call-to-Action**: 명확한 행동 유도

### 3. Platform-Specific Optimization
각 플랫폼에 최적화된 콘텐츠 변형:

#### Instagram
- **Visual Storytelling**: 시각적 스토리텔링
- **Hashtag Strategy**: 해시태그 전략
- **Story Features**: 스토리 기능 활용
- **Reel Trends**: 릴 트렌드 반영

#### YouTube  
- **SEO Optimization**: 검색 최적화
- **Thumbnail Design**: 썸네일 전략
- **Engagement Tactics**: 참여 유도 방법
- **Series Planning**: 시리즈 콘텐츠 기획

#### LinkedIn
- **Professional Tone**: 전문적 톤앤매너
- **Industry Insights**: 업계 인사이트
- **Thought Leadership**: 사고 리더십
- **Network Engagement**: 네트워크 참여

### 4. Content Creation Execution
- **Creative Concepts**: 3-5개 크리에이티브 컨셉
- **Content Calendar**: 4주 콘텐츠 캘린더
- **Production Guide**: 제작 가이드라인
- **Performance Metrics**: 성과 측정 지표

## 🎯 High-Converting Content Elements
- **Attention-Grabbing Headlines**: 클릭을 유도하는 헤드라인
- **Emotional Triggers**: 감정적 반응 유도 요소
- **Social Proof**: 사회적 증거와 신뢰 구축
- **Scarcity & Urgency**: 희소성과 긴급성 활용

## ⚡ GPT5 최적화
"Create compelling, platform-optimized content that drives engagement and conversions"
```

## 🏥 전문 서비스 도메인

### 의료 진단 지원 패턴
```markdown
# 의료 진단 지원 프롬프트 패턴

## 🏥 진단 지원 요청
[환자 기본정보, 주증상, 검사 결과, 의료진 질의]

## ⚕️ 임상 추론 프레임워크
다음 의학적 추론 과정을 따라 분석해주세요:

### 1. Clinical Data Analysis
- **Chief Complaint**: 주 호소 증상 분석
- **History of Present Illness**: 현병력 패턴 분석
- **Review of Systems**: 계통별 증상 검토
- **Physical Examination**: 신체 검진 소견 해석

### 2. Differential Diagnosis
- **Primary Diagnosis**: 가장 가능성 높은 진단
  - Supporting Evidence: [근거들]
  - Probability: [확률 추정]
- **Alternative Diagnoses**: 감별 진단들
  - Differential Points: [감별점들]
  - Additional Tests: [추가 필요 검사]

### 3. Evidence-Based Assessment
- **Literature Review**: 관련 연구 근거
- **Clinical Guidelines**: 진료 가이드라인 준수
- **Risk Stratification**: 위험도 분층화
- **Prognosis**: 예후 평가

## ⚠️ 중요 주의사항
- 이는 의료진의 임상 판단을 보조하는 정보입니다
- 최종 진단과 치료는 반드시 의료진이 결정해야 합니다
- 응급 상황 시 즉시 응급실 방문을 권합니다

## ⚡ GPT5 최적화
"Provide clinical decision support with medical expertise while emphasizing the need for professional medical judgment"
```

### 법률 분석 패턴
```markdown
# 법률 분석 프롬프트 패턴

## ⚖️ 법률 자문 요청
[사안 개요, 관련 사실관계, 쟁점 사항, 관할 지역]

## 📚 법률 분석 프레임워크
다음 법률적 추론 구조를 따라 분석해주세요:

### 1. Issue Identification (쟁점 정리)
- **Legal Issues**: 핵심 법적 쟁점들
- **Factual Issues**: 사실관계상 쟁점들
- **Procedural Issues**: 절차적 쟁점들
- **Jurisdictional Issues**: 관할권 관련 쟁점

### 2. Legal Research & Authority
#### Primary Authority
- **Statutes**: 관련 법령 조항
- **Case Law**: 판례 분석
- **Regulations**: 시행령 및 규칙
- **Constitutional Provisions**: 헌법적 쟁점

#### Secondary Authority  
- **Legal Commentary**: 법학자 견해
- **Practice Guides**: 실무 가이드
- **Law Review Articles**: 법학 논문
- **Comparative Law**: 비교법적 검토

### 3. Legal Analysis (IRAC Method)
각 쟁점별로:
- **Issue**: 쟁점 정의
- **Rule**: 적용 법리
- **Analysis**: 사안에의 적용
- **Conclusion**: 결론 및 예상 결과

### 4. Strategic Recommendations
- **Legal Options**: 가능한 법적 대응 방안
- **Risk Assessment**: 각 방안의 위험도
- **Cost-Benefit Analysis**: 비용 대비 효과
- **Timeline**: 예상 소요 시간

## ⚠️ 법적 고지
- 이는 일반적인 법률 정보 제공입니다
- 구체적 법률 자문은 변호사와 상담하시기 바랍니다
- 관할 지역의 법령과 판례를 반드시 확인하세요

## ⚡ GPT5 최적화
"Analyze this legal matter with the thoroughness of an experienced attorney, emphasizing the need for professional legal counsel"
```

이러한 도메인별 특화 패턴을 활용하여 각 전문 분야에서 GPT5의 역량을 최대한 발휘하세요!