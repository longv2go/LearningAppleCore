#!/bin/bash
#从命令行获取用户名，ID以及全名

USER=$1
ID=$2
FULLNAME=$3

#创建用户节点
dscl . -create /Users/$USER

#将默认shell设置为zsh
dscl . -create /Users/$USER UserShell /bin/zsh

#设置GECOS（finger的全名）
dscl . -create /Users/$USER RealName "$FULLNAME"
dscl . -create /Users/$USER UniqueID $ID

#将用户gid设置位localaccounts的gid
dscl . -create /Users/$USER PrimaryGroupID 61

#设置home 目录
dscl . -create /Users/$USER NFSHomeDirectory /Users/$USER

#确保home目录是可用的， 且属于用户所有
mkdir /Users/$USER
chown  $USER /Users/$USER

#设置密码
dscl . -passwd /Users/$USER "changeme"

#添加到admin组
dscl . -create /Groups/admin GroupMembership $USER
