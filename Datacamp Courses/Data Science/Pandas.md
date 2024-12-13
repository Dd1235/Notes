# Some notes on the syntax

.columns
.index : contains row numbers or row names, index objects
.shape
.describe()
.info() : gives a concise summary of the dataframe
.dtypes()
.values : gives the values in the dataframe as a numpy array
Subsesetting cols:  df[['col1', 'col2']]
Subsetting rows: df[0:4] or df['row_label'], df[(df["col"] > 160) &( df[..] == ..)\] (using logical conditions)
Subsetting using isin(): df[df["col"].isin(["val1", "val2"])]
Sort rows: df.sort_values(["col1"], ascending = [False])