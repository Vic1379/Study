def to_n(x): return((ord(x[0])-64, int(x[1])))
def to_s(x): return chr(x[0]+64)+str(x[1])
def is_in(x): return (True if (x[0]<9 and x[0]>0 and x[1]<9 and x[1]>0) else False)
def m_sum(x, y): return (x[0]+y[0], x[1]+y[1])
def list_of_turns(cell): return list(to_s(i) for i in filter(is_in, (m_sum(to_n(cell), i) for i in ((-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)))))