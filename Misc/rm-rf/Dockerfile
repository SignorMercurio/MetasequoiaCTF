FROM glzjin/pwn_base_16
COPY pwn /pwn/pwn

RUN  rm -rf /bin/cat /bin/more /bin/less /bin/grep /bin/fgrep /bin/egrep /sbin/apk /bin/base64 && \
      mv /usr/bin/timeout /usr/ && \
      rm -rf /usr/bin/* && \
      mv /usr/timeout /usr/bin/ && \
      rm -rf /bin/rmdir /bin/rm