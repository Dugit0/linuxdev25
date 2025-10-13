set pagination off
b 30

start -100 100 3 > /dev/null
ignore 1 27
set $i = 0
while $i < 8
    continue
    printf "@@@%d %d %d %d\n", m, n, s, i
    set $i = $i + 1
end
quit
