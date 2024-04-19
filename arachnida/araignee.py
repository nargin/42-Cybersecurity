from bs4 import BeautifulSoup
import argparse

def main():
    parser = argparse.ArgumentParser(description='Extract data from a web page', prog='Arachnida')
    parser.add_argument("-r", "--recursively", help="Recursively extract data from all links", action="store_true")
    parser.add_argument("-l", "--level", help="Depth level limit for recursive extraction", type=int, default=5)
    parser.add_argument("-p", "--path", help="Path to save the data extracted (default: ./data/)", default="./data/")

    args = parser.parse_args()

    print(args)

if __name__ == "__main__":
    main()