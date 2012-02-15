scc 'auto P = pair<int,float>{1,3.3};  __ P, ++P, P++'
scc 'auto P = tuple<int,float>{1,3.3};  __ P, ++P, P++;'
scc 'vint S{1,2,3}, T;  S>>T; T'
scc 'vint v{1,2};  auto __ (+v/-v=11);  __ (range(v)=22);  __ (v|rng = 33) ;'
