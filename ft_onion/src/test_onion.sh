#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

USERNAME="robin"

echo "!!! TEST ONLY WORK IF SSH_USER (.env) IS '${USERNAME}' !!!\n"

print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}OK${NC} - $2"
    else
        echo -e "${RED}KO${NC} - $2"
    fi
}

echo "Username from .env file: $SSH_USER"

# Rest of your checks...
echo "Checking if SSH is listening on port 4242..."
ss -tuln | grep -q ':4242'
print_result $? "SSH listening on port 4242"

# SSH security configuration checks...
echo "Checking SSH security configurations..."
grep -Eq "^PermitRootLogin no" /etc/ssh/sshd_config
print_result $? "PermitRootLogin disabled"

grep -Eq "^PasswordAuthentication yes" /etc/ssh/sshd_config
print_result $? "PasswordAuthentication enabled"

grep -Eq "^ChallengeResponseAuthentication no" /etc/ssh/sshd_config
print_result $? "ChallengeResponseAuthentication disabled"

grep -Eq "^UsePAM yes" /etc/ssh/sshd_config
print_result $? "UsePAM enabled"

grep -Eq "^X11Forwarding no" /etc/ssh/sshd_config
print_result $? "X11Forwarding disabled"

echo "Testing SSH connection via Tor..."
ONION_ADDRESS=$(cat /var/lib/tor/hidden_service/hostname)
if [ -z "$ONION_ADDRESS" ]; then
    echo -e "${RED}KO${NC} - Could not obtain .onion address"
    exit 1
else
    echo "Obtained .onion address: $ONION_ADDRESS"
fi

echo "Testing interactive SSH prompt via Tor..."
ssh -o StrictHostKeyChecking=no -o ProxyCommand="nc -x 127.0.0.1:9050 %h %p" -p 4242 "${USERNAME}@${ONION_ADDRESS}"

echo "Tests completed."