def generate_graph(trans_func, start_state, final_states):
	states = trans_func.keys()
	states.sort()
	dot_graph = 'digraph finite_state_machine {\n'
	dot_graph += ' rankdir=LR;\n'
	dot_graph += ' edge [fontname=arial,fontsize=11]\n'
	dot_graph += ' node [fontname=arial,fontsize=11,shape=doublecircle];'
	dot_graph += ' '.join(final_states)
	dot_graph += ';\n'
	dot_graph += ' node [shape=circle,size=8]\n'
	dot_graph += ' start [shape=point]\n'
	dot_graph += ' start -> %s\n' % start_state
	for state in states:
		values = trans_func[state].keys()
		values.sort()
		for value in values:
			dot_graph += ' %s -> %s [label=%s]\n' % \
					(state, trans_func[state][value], value)
	dot_graph += '}\n'
	return dot_graph
