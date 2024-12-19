#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}OK${NC} - $2"
    else
        echo -e "${RED}KO${NC} - $2"
    fi
}

echo "Verificando se o SSH está escutando na porta 4242..."
ss -tuln | grep -q ':4242'
print_result $? "SSH escutando na porta 4242"

echo "Verificando configurações de segurança do SSH..."
grep -Eq "^PermitRootLogin no" /etc/ssh/sshd_config
print_result $? "PermitRootLogin desabilitado"

grep -Eq "^PasswordAuthentication yes" /etc/ssh/sshd_config
print_result $? "PasswordAuthentication habilitado"

grep -Eq "^ChallengeResponseAuthentication no" /etc/ssh/sshd_config
print_result $? "ChallengeResponseAuthentication desabilitado"

grep -Eq "^UsePAM yes" /etc/ssh/sshd_config
print_result $? "UsePAM habilitado"

grep -Eq "^X11Forwarding no" /etc/ssh/sshd_config
print_result $? "X11Forwarding desabilitado"

echo "Testando a conexão SSH via Tor..."
ONION_ADDRESS=$(cat /var/lib/tor/hidden_service/hostname)
if [ -z "$ONION_ADDRESS" ]; then
    echo -e "${RED}KO${NC} - Não foi possível obter o endereço .onion"
    exit 1
else
    echo "Obtido endereço .onion: $ONION_ADDRESS"
fi

echo "Testando o prompt interativo SSH via Tor..."
ssh -o StrictHostKeyChecking=no -o ProxyCommand="nc -x 127.0.0.1:9050 %h %p" -p 4242 caalbert@$ONION_ADDRESS

echo "Testes concluídos."
