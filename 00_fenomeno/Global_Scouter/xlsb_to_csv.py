import pandas as pd
import argparse
import os

def convert_xlsb_to_csv(input_file, output_file_base, sheet_identifier=0):
    """
    Converts specified sheets from an XLSB file to CSV file(s).

    Args:
        input_file (str): Path to the input XLSB file.
        output_file_base (str): Base path for the output CSV file(s).
                                 If converting all sheets, sheet name will be appended.
        sheet_identifier (int or str or list, optional):
                                           - 0 for the first sheet (default)
                                           - Sheet index (int) or name (str) for a single sheet.
                                           - "all" (str) to convert all sheets.
    """
    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found.")
        return

    try:
        xls = pd.ExcelFile(input_file, engine="pyxlsb")

        # Determine the output directory
        output_dir = os.path.dirname(output_file_base)
        input_file_name_without_ext = os.path.splitext(os.path.basename(input_file))[0]
        
        # Create a new subdirectory for output if converting all sheets
        if sheet_identifier == "all":
            specific_output_folder = os.path.join(output_dir, input_file_name_without_ext)
            os.makedirs(specific_output_folder, exist_ok=True)
            print(f"Output will be saved in: '{specific_output_folder}'")
        else:
            specific_output_folder = output_dir # For single sheet, use the provided output_file_base's directory

        if sheet_identifier == "all":
            sheet_names = xls.sheet_names
            print(f"Converting all sheets from '{input_file}'...")
            for sheet_name in sheet_names:
                df = xls.parse(sheet_name)
                # Construct output filename: append sheet name before .csv extension, and place in new folder
                name, ext = os.path.splitext(os.path.basename(output_file_base)) # Use basename for constructing new file name
                current_output_file = os.path.join(specific_output_folder, f"{input_file_name_without_ext}_{sheet_name}.csv")
                df.to_csv(current_output_file, index=False)
                print(f"Successfully converted sheet '{sheet_name}' to '{current_output_file}'.")
        else:
            df = xls.parse(sheet_identifier)
            # For single sheet, output_file_base is the full path including filename
            df.to_csv(output_file_base, index=False)
            print(f"Successfully converted sheet '{sheet_identifier}' from '{input_file}' to '{output_file_base}'.")

    except ValueError as e:
        print(f"Error converting file: {e}. Make sure the sheet name/index is correct.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
    finally:
        print("\nConversion process completed. Done.") # Final "Done" message

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Convert an XLSB file to a CSV file(s).",
        formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("input_xlsb", help="Path to the input .xlsb file.")
    parser.add_argument("output_csv_base", help="Base path for the output .csv file(s). "
                                                "If converting all sheets, a new folder named after the input XLSB file will be created "
                                                "at this path's directory, and all CSVs will be placed inside it. "
                                                "For single sheet conversion, this is the full output CSV file path.")
    parser.add_argument(
        "-s", "--sheet",
        dest="sheet_identifier",
        default=0,
        help="Specify the sheet to convert.\n" 
             "Use 0 for the first sheet (default), 1 for the second, and so on.\n" 
             "Alternatively, provide the exact sheet name as a string.\n" 
             "Use 'all' to convert all sheets into separate CSV files."
    )

    args = parser.parse_args()

    # Determine sheet_identifier type
    if args.sheet_identifier == 'all':
        sheet_to_convert = 'all'
    else:
        try:
            sheet_to_convert = int(args.sheet_identifier)
        except ValueError:
            sheet_to_convert = args.sheet_identifier

    convert_xlsb_to_csv(args.input_xlsb, args.output_csv_base, sheet_to_convert)
