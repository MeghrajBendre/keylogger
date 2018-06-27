# keylogger

As the name suggests, this is a simple keylogger application which uses Linux input subsystem's event interface. The keyboard device is detected automatically and the logger is aware of `Shift` key modifier. It stores almost all the keys pressed by the user in a log file located at var/log/key.log.

# Usage

1. Clone the repository  
`git clone https://meghraj_bendre@bitbucket.org/meghraj_bendre/keylogger.git`  
  
2. Build code  
`make`  
  
3. Run  
`sudo ./keylogger`  
  
# Start on boot  

1. Edit /etc/rc.local and add /path/to/keylogger above the line with exit 0. Replace /path/to/keylogger with the full path to the keylogger binary.

2. Allow sudo access without a password. To do this, add the following line to /etc/sudoers making sure to replace the path with the path you used above and the username with your username:  
`username ALL = NOPASSWD: /path/to/keylogger`  
3. Reboot Ubuntu. Open a terminal and type pgrep keylogger. You should find one keylogger process running.

# Disclaimer

This code was created entirely out of an interest in learning about linux keyboard events. It should never be used on any machine where you are not authorised to log keystrokes.