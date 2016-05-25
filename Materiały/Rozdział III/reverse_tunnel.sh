#!/bin/bash
 
createTunnel() {
  /usr/bin/ssh -f -NT -R 0.0.0.0:6789:localhost:8000 piecia@pidronx.ddns.net -p 30
  /usr/bin/ssh -f -NT -R 0.0.0.0:6790:localhost:8080 piecia@pidronx.ddns.net -p 30
  if [[ $? -eq 0 ]]; then
    echo Reverse tunnel Rpi <=> Ubuntu created successfully
  else
    echo An error occurred creating a reverse tunnel
  fi
}
/bin/pidof ssh
if [[ $? -ne 0 ]]; then
  echo Creating new reverse tunnel connection
  createTunnel
fi
