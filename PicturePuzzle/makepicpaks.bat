pushd picpaks
for /h /a:d %x in (*) do picpak -ow+ "%x" "%x"
copy *.picpak ..
popd
