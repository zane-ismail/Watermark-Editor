prompt = input("Greeting: ").lower().strip()
if prompt[0:5] == "hello":
    print("$0")
elif prompt[0][0] == 'h':
    print("$20")
else:
    print("$100")