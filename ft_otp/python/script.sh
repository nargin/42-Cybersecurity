#!/bin/bash

./gen -f # -n 128

random_key=$(cat hex.key)

python3 ft_otp.py -g $random_key

my_totp=$(python3 ft_otp.py -k -qr)
echo "My TOTP: $my_totp"

oauth_totp=$(oathtool --totp $random_key)
echo "OAuth TOTP: $oauth_totp"

rm hex.key ft_otp.key
