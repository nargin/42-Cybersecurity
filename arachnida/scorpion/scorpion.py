import argparse
import os
import json
import subprocess
from PIL import Image
from PIL.ExifTags import TAGS

Extension = ["png", "jpg", "jpeg", "gif", "bmp"]

def isFileValid(file):
    ext = file.split(".")[-1].lower()
    if not os.path.exists(file):
        raise FileNotFoundError(f"File {file} not found")
    if not os.path.isfile(file):
        raise ValueError(f"{file} is not a file")
    if not os.access(file, os.R_OK):
        raise PermissionError(f"Permission denied to read {file}")
    if ext not in Extension:
        raise ValueError(f"File {file} is not an image file")

def run_exiftool(args):
    try:
        result = subprocess.run(['exiftool'] + args, capture_output=True, text=True)
        if result.returncode != 0:
            raise Exception(result.stderr)
        return result.stdout
    except FileNotFoundError:
        raise Exception("ExifTool not found. Please install ExifTool or add it to your PATH.")

def display_metadata(file):
    try:
        metadata = run_exiftool([file])
        print(metadata)
    except Exception as e:
        print(f"Error displaying metadata: {str(e)}")
        print("Falling back to PIL for basic metadata...")
        display_metadata_pil(file)

def display_metadata_pil(file):
    try:
        with Image.open(file) as img:
            exif = img._getexif()
            if exif:
                print(json.dumps({TAGS.get(k, k): v for k, v in exif.items()}, indent=4))
            else:
                print("No EXIF metadata found.")
    except Exception as e:
        print(f"Error reading metadata with PIL: {str(e)}")

def modify_metadata(file, tag, value):
    try:
        output = run_exiftool([f'-{tag}={value}', file])
        print(output)
    except Exception as e:
        print(f"Error updating metadata: {str(e)}")

def main():
    parser = argparse.ArgumentParser(description='Metadata of a file', prog='Scorpion')
    parser.add_argument("file", help="File to extract or modify metadata", type=str, nargs="+")
    parser.add_argument("-m", "--modify", nargs=2, metavar=("TAG", "VALUE"), help="Modify metadata tag")
    args = parser.parse_args()

    for file in args.file:
        isFileValid(file)

    if args.modify:
        tag, value = args.modify
        for file in args.file:
            modify_metadata(file, tag, value)
    
    for file in args.file:
        print(f"\nMetadata for {file}:")
        display_metadata(file)

if __name__ == "__main__":
    main()