# • Your program must take arguments.
# ◦ -g: The program receives as argument a hexadecimal key of at least 64 characters. The program stores this key safely in a file called ft_otp.key, which
# is encrypted.
# ◦ -k: The program generates a new temporary password based on the key given
# as argument and prints it on the standard output.

import argparse
import base64
import pyotp

    # base32_key = base64.b32encode(bytes.fromhex(key))
    # print(base32_key)
    # hotp = pyotp.HOTP(base32_key)
    # print(hotp.at(0))

def generate_password(key):
    if len(key) < 64:
        exit("Key must be at least 64 characters long")
    if not all(c in '0123456789abcdefABCDEF' for c in key):
        exit("Key must be hexadecimal")
    base32_key = base64.b32encode(bytes.fromhex(key))
    with open('ft_otp.key', 'wb') as f:
        f.write(base32_key)

def main():
    parser = argparse.ArgumentParser(description='OTP generator')
    parser.add_argument('-g', '--generate', type=str, help='Generate a new key')
    parser.add_argument('-k', '--key', type=str, help='Generate a new password based on the key')
    args = parser.parse_args()

    print(args)

    # if args.generate:
    #     generate_key(args.generate)
    # elif args.key:
    generate_password(args.key)
    # else:
        # parser.print_help()

if __name__ == '__main__':
    main()