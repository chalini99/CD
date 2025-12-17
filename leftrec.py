def eliminate_left_recursion(non_terminal, productions):
    alpha = []
    beta = []

    for prod in productions:
        if prod.startswith(non_terminal):
            alpha.append(prod[len(non_terminal):])
        else:
            beta.append(prod)

    if not alpha:
        print("No left recursion found.")
        return

    new_nt = non_terminal + "'"

    print(f"{non_terminal} → ", end="")
    print(" | ".join(b + new_nt for b in beta))

    print(f"{new_nt} → ", end="")
    print(" | ".join(a + new_nt for a in alpha) + " | ε")


# Example
non_terminal = "A"
productions = ["Aa", "Ab", "c", "d"]

eliminate_left_recursion(non_terminal, productions)
