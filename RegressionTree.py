import numpy as np, shap, catboost
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_boston

X, y = shap.datasets.boston()
X_train, X_test, y_train, y_test = train_test_split(X, y)
reg = catboost.CatBoostRegressor(iterations = 1000, learning_rate = 0.25, silent = True)
reg.fit(X_train, y_train, eval_set=(X_test, y_test))
explainer = shap.TreeExplainer(reg)
shap_values = explainer.shap_values(X)
print(load_boston().DESCR)
shap.summary_plot(shap_values, X, plot_type="bar")
n = np.random.randint(0, 506)
print(y[n])
shap.force_plot(explainer.expected_value, shap_values[n], X.iloc[n], matplotlib = True)