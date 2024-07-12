all: check-python

.PHONY: check-python
check-python:
	black --line-length 120 --check ccc.py
	pylint --max-line-length 120 ccc.py --disable too-many-statements,too-many-branches,too-many-locals,too-many-nested-blocks,too-few-public-methods,redefined-outer-name
	mypy --strict ccc.py
