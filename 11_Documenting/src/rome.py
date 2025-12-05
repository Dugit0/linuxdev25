def to_roman_numeral(num):
    """
    Converts an integer to its Roman numeral representation.
    Assumes the input integer is between 1 and 3999 (inclusive).
    """
    if not 1 <= num <= 3999:
        raise ValueError("Input number must be between 1 and 3999.")

    lookup = [
        (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
        (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
        (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'),
        (1, 'I')
    ]

    result = ''
    for value, roman_symbol in lookup:
        while num >= value:
            result += roman_symbol
            num -= value
    return result

arr = [f'"{to_roman_numeral(i)}"' for i in range(1, 101)]
arr.insert(0, '""')
print(len(arr), max(map(len, arr)))
print(f"{{{', '.join(arr)}}}")
