def calculate_interest():
    years = int(input("How many years do you want to invest? "))
    monthly_investment = float(input("How much money will you invest each month? "))
    interest_rate = float(input("What is the annual interest rate (in percentage)? ")) / 100
    currency = input("What is the currency? ")
    is_currency_before = input("Is the currency symbol/word before the value? (yes/no) ") == 'yes'
    thousands_sep = input("What thousands separator would you like to use? ")

    money = 0.0
    interest_per_month = interest_rate / 12

    md_table = "| Year | Month | Money gained from Interest | Total Money |\n|------|-------|---------------------------|-------------|\n"

    for year in range(1, years + 1):
        for month in range(1, 13):
            gained_interest = money * interest_per_month
            money += gained_interest + monthly_investment

            money_string = f"{currency}{format(money, ',.2f').replace(',', thousands_sep)}" if is_currency_before else f"{format(money, ',.2f').replace(',', thousands_sep)}{currency}"
            gained_interest_string = f"{currency}{format(gained_interest, ',.2f').replace(',', thousands_sep)}" if is_currency_before else f"{format(gained_interest, ',.2f').replace(',', thousands_sep)}{currency}"

            md_table += f"| {year} | {month} | {gained_interest_string} | {money_string} |\n"
            
    with open("interest_report.md", "w") as file:
        file.write(md_table)

    return md_table

print(calculate_interest())

