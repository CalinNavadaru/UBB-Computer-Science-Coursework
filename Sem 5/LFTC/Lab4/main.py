import af

file = "af_integers_c_plus_plus.txt"
file2 = "af_clasa.txt"

af = af.AF()
af.get_from_file(file)
print(f"0XABCDEF: {af.evaluate("0XABCDEF")}")
print(f"+0XABCDEF: {af.evaluate("+0XABCDEF")}")
print(f"-0XABCDEF: {af.evaluate("-0XABCDEF")}")
print(f"+123: {af.evaluate("+123")}")
print(f"0: {af.evaluate("0")}")
print(f"0ull: {af.evaluate("0ull")}")
print(f"0e123t: {af.get_longest_prefix("0e123t")}")

af.get_from_file(file2)
print(af.evaluate("aabb"))
print(af.evaluate("bbb"))
print(af.evaluate("aa"))
print(af.evaluate("abc"))
print(af.get_longest_prefix("aaabbbbcdedf"))