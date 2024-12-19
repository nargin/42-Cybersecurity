#!/bin/bash

echo "Starting SSH service..."
service ssh restart

echo "Checking Nginx configuration..."
nginx -t
if [ $? -ne 0 ]; then
  echo "Nginx configuration error. Exiting..."
  exit 1
fi

echo "Starting Nginx service..."
service nginx start

echo "Starting Tor service..."
service tor start

echo "Waiting for Tor to create the hidden service directory..."
for i in {1..20}; do
    if [ -f /var/lib/tor/hidden_service/hostname ]; then
        echo "Tor directory created."
        break
    fi
    echo "Tor directory not created yet, retrying in 2 seconds..."
    sleep 2
done

if [ ! -f /var/lib/tor/hidden_service/hostname ]; then
  echo "Tor did not create the hidden service directory. Exiting..."
  exit 1
fi

echo "All services started. Keeping the container running..."
tail -f /dev/null
