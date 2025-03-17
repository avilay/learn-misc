from colorama import Fore, Back, Style


def main():
    print(Fore.RED + "some red text")
    print(Back.GREEN + "and with a green background")
    print(Style.DIM, "and in dim text")
    print(Style.RESET_ALL)
    print("Back to normal now")


if __name__ == "__main__":
    main()
