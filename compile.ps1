# https://gbatemp.net/threads/converting-elf-to-cia-how.399353/
make clean
make
./bannertool.exe makebanner -i banner.png -a sound.wav -o banner.bnr
./bannertool.exe makesmdh -s "Battery Percentage Viewer" -l "Battery Percentage Viewer" -p "Pavlos Efstathiou" -i icon.png -o Battery.smdh
./bannertool.exe makesmdh -s "Battery Percentage Viewer" -l "Battery Percentage Viewer" -p "Pavlos Efstathiou" -i icon.png -o icon.icn
./makerom.exe -f cia -o battery-viewer.cia -DAPP_ENCRYPTED=false -rsf cia.rsf -target t -exefslogo -elf Battery.elf -icon icon.icn -banner banner.bnr
echo "Complete!"
