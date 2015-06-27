@echo off
SET PATH=%PATH%;
SET linux_host=192.168.0.25
SET linux_user=dippi
SET identity_file=C:\Users\root\.ssh\id_rsa
SET linux_destination=~/sani/
SET file_list=(premake4.lua src include tests thirdparty run_tests.sh)

for %%i in %file_list% do scp -i %identity_file% -r %%i %linux_user%@%linux_host%:%linux_destination%