set pagination off
b 30 if i % 5 == 0
command 1
    printf "@@@%d %d %d %d\n", m, n, s, i
    continue
end

run 1 12 > /dev/null
quit
