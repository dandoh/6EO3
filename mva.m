Z = 25;
mu = [1/2 1/4 1/4 1/4 1/4];
V = [2 1/4 1/4 1/4 1/4];
M = 10;
n = [0 0 0 0 0];
t = [0 0 0 0 0];
N = 5;
bus = 1;

%
% Main MVA loop
%
for j=1:M
	for i=1:N
		t(i)=1/mu(i)*(1+n(i));
	end
	den=Z;
	for i=1:N
		den=den+V(i)*t(i);
	end
	through=j/den;
	for i=1:N
		n(i)=t(i)*V(i)*through;
	end

  j
	request_rt = 2 * t(1) + t(2)
	utilization = through * V(bus) / mu(bus)
end


