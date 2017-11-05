// TIME
for (int a = 0; ;++a){
    if (clock()>=2.5*CLOCKS_PER_SEC) break;
    // It will stop when 2.5 seconds have passed
}


// LAMBDA
function<bool(int, int)> add_edge = [&](int u, int v)
{
    // code here...
    return true;
};

// RANDOM DISTRIBUTIONS
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
