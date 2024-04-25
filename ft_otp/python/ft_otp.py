# • Your program must take arguments.
# ◦ -g: The program receives as argument a hexadecimal key of at least 64 characters. The program stores this key safely in a file called ft_otp.key, which
# is encrypted.
# ◦ -k: The program generates a new temporary password based on the key given
# as argument and prints it on the standard output.

import argparse
import base64
import pyotp
import time
import os

def generate_password(key: str):
	if len(key) < 64:
		exit("Key must be at least 64 characters long")
	if not all(c in '0123456789abcdefABCDEF' for c in key):
		exit("Key must be hexadecimal")
	base32_key = base64.b32encode(bytes.fromhex(key))
	with open('ft_otp.key', 'wb') as f:
		f.write(base32_key)
	print("Password generated in ft_otp.key")

def generate_key():
	if not os.path.exists('ft_otp.key'):
		exit("No key found")
	with open('ft_otp.key', 'rb') as f:
		base32_key = f.read()
		hotp = pyotp.HOTP(base32_key)
		timestamp = int(time.time() / 30)
		totp = hotp.at(timestamp)
		print(totp)

def in_venv():
	if os.getenv('VIRTUAL_ENV') is None:
		exit('Please run the script in a virtual environment')

def main():
	in_venv()
	parser = argparse.ArgumentParser(description='OTP generator')
	parser.add_argument('-g', '--generate', type=str, help='Generate a new key')
	parser.add_argument('-k', '--key', help='Generate a new password based on the key', action='store_true')
	args = parser.parse_args()

	if args.generate:
	    generate_password(args.generate)
	elif args.key:
		generate_key()

if __name__ == '__main__':
	main()