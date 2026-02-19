import pandas as pd

equity_distributions = pd.read_csv("equity_results.csv", header = None)

equity_distribution_weights = pd.read_csv("equity_weights.csv", header = None)

print(equity_distributions.head())

print(equity_distribution_weights.shape)
