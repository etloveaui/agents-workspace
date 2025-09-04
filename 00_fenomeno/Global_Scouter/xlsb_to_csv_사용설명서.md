# xlsb_to_csv.py 사용 설명서

이 문서는 `xlsb_to_csv.py` 스크립트를 사용하여 `.xlsb` 파일을 `.csv` 파일로 변환하는 방법을 설명합니다.

## 1. 스크립트 목적

`.xlsb` (Excel Binary Workbook) 파일의 데이터를 `.csv` (Comma Separated Values) 형식으로 변환합니다. 특정 시트만 변환하거나, 파일 내의 모든 시트를 각각의 `.csv` 파일로 추출할 수 있습니다.

## 2. 준비물

이 스크립트를 실행하려면 Python과 다음 라이브러리가 설치되어 있어야 합니다.
*   `pandas`
*   `pyxlsb`
*   `openpyxl` (pandas가 Excel 파일을 처리하는 데 필요할 수 있습니다.)

**스크립트 실행 전 반드시 설치해야 합니다.** 설치되지 않았다면, 명령 프롬프트(또는 터미널)에서 다음 명령어를 실행하여 설치할 수 있습니다:
```bash
pip install pandas pyxlsb openpyxl
```

## 3. 사용 방법

스크립트는 명령 프롬프트(또는 터미널)에서 실행합니다. 스크립트 실행 시 현재 작업 디렉토리에 따라 경로를 다르게 지정해야 합니다.

### 3.1 프로젝트 루트 디렉토리에서 실행하는 경우 (권장)

현재 작업 디렉토리가 `C:\Users\eunta\agents-workspace`와 같이 프로젝트의 최상위 디렉토리인 경우입니다. 이 경우 모든 파일 경로를 프로젝트 루트 기준으로 지정합니다.

**명령어 형식:**
```bash
python 00_fenomeno/Global_Scouter/xlsb_to_csv.py [입력_xlsb_파일_경로] [출력_csv_파일_경로]
```

**예시:**
`Global_Scouter_20250829.xlsb` 파일의 첫 번째 시트를 `Global_Scouter_20250829.csv`로 변환합니다.
```bash
python 00_fenomeno/Global_Scouter/xlsb_to_csv.py 00_fenomeno/Global_Scouter/Global_Scouter_20250829.xlsb 00_fenomeno/Global_Scouter/Global_Scouter_20250829.csv
```

### 3.2 스크립트가 있는 디렉토리에서 실행하는 경우

현재 작업 디렉토리가 `C:\Users\eunta\agents-workspace\00_fenomeno\Global_Scouter`와 같이 `xlsb_to_csv.py` 스크립트가 있는 디렉토리인 경우입니다. 이 경우 스크립트 이름만 지정하고, 입출력 파일 경로는 현재 디렉토리 기준으로 지정합니다.

**명령어 형식:**
```bash
python xlsb_to_csv.py [입력_xlsb_파일_경로] [출력_csv_파일_경로]
```

**예시:**
`Global_Scouter_20250829.xlsb` 파일의 첫 번째 시트를 `Global_Scouter_20250829.csv`로 변환합니다.
```bash
python xlsb_to_csv.py Global_Scouter_20250829.xlsb Global_Scouter_20250829.csv
```

### 3.3 특정 시트 변환

`.xlsb` 파일 내의 특정 시트(이름 또는 인덱스)를 `.csv` 파일로 변환합니다.

**명령어 형식:**
```bash
python [스크립트_경로] [입력_xlsb_파일_경로] [출력_csv_파일_경로] -s [시트_이름_또는_인덱스]
```

**예시 (프로젝트 루트에서 실행):**
*   `Global_Scouter_20250829.xlsb` 파일의 두 번째 시트(인덱스 1)를 `Global_Scouter_20250829_Sheet2.csv`로 변환합니다.
    ```bash
    python 00_fenomeno/Global_Scouter/xlsb_to_csv.py 00_fenomeno/Global_Scouter/Global_Scouter_20250829.xlsb 00_fenomeno/Global_Scouter/Global_Scouter_20250829_Sheet2.csv -s 1
    ```
*   `Global_Scouter_20250829.xlsb` 파일 내 "Summary"라는 이름의 시트를 `Global_Scouter_20250829_Summary.csv`로 변환합니다.
    ```bash
    python 00_fenomeno/Global_Scouter/xlsb_to_csv.py 00_fenomeno/Global_Scouter/Global_Scouter_20250829.xlsb 00_fenomeno/Global_Scouter/Global_Scouter_20250829_Summary.csv -s "Summary"
    ```

### 3.4 모든 시트 한 번에 변환 (추천)

`.xlsb` 파일 내의 모든 시트를 각각 별도의 `.csv` 파일로 변환합니다. 각 `.csv` 파일의 이름에는 해당 시트의 이름이 포함됩니다.

**명령어 형식:**
```bash
python [스크립트_경로] [입력_xlsb_파일_경로] [출력_csv_파일_기본_경로] -s all
```

**예시 (프로젝트 루트에서 실행):**
`Global_Scouter_20250829.xlsb` 파일의 모든 시트를 변환합니다.
```bash
python 00_fenomeno/Global_Scouter/xlsb_to_csv.py 00_fenomeno/Global_Scouter/Global_Scouter_20250829.xlsb 00_fenomeno/Global_Scouter/Global_Scouter_20250829.csv -s all
```
*   **출력 파일명 예시:** 만약 원본 파일에 "Sheet1", "Data"라는 시트가 있다면, `Global_Scouter_20250829_Sheet1.csv`, `Global_Scouter_20250829_Data.csv`와 같이 생성됩니다.

## 4. 참고 사항

*   **매크로(VBA) 포함 여부:** `.xlsb` 파일에 매크로가 포함되어 있더라도 데이터 추출에는 영향을 미치지 않습니다. 이 스크립트는 시트의 데이터 내용만 읽어 변환하며, 매크로를 실행하거나 해석하지 않습니다.
*   **시트 이름 확인:** 어떤 시트를 변환해야 할지 확실하지 않다면, 다음 Python 코드를 사용하여 `.xlsb` 파일 내의 모든 시트 이름을 먼저 확인할 수 있습니다.
    ```python
    import pandas as pd
    xlsb_file_path = "00_fenomeno/Global_Scouter/Global_Scouter_20250829.xlsb" # 실제 파일 경로로 변경
    try:
        xls = pd.ExcelFile(xlsb_file_path, engine="pyxlsb")
        print(f"'{xlsb_file_path}' 파일의 시트 목록:")
        for i, name in enumerate(xls.sheet_names):
            print(f"  - [{i}] {name}")
    except Exception as e:
        print(f"시트 이름을 읽는 중 오류 발생: {e}")
    ```