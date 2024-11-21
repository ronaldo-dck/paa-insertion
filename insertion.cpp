#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <climits>

std::vector<int> insertion_sort(std::vector<int> &nums)
{

    int i = 1;
    int j = 0;
    while (i < nums.size())
    {
        j = i;
        while (j > 0 && nums[j - 1] > nums[j])
        {
            int aux = nums[j];
            nums[j] = nums[j - 1];
            nums[j - 1] = aux;
            j--;
        }
        i++;
    }
    return nums;
}

std::vector<int> bucket_sort(int n_buckets, std::vector<int> nums, int low, int high)
{
    std::vector<std::vector<int>> buckets(n_buckets);

    int range = high - low;

    for (int num : nums)
    {
        int bucketIndex = int((float(num - low) / range) * (n_buckets));
        if (num == high)
        {
            buckets[n_buckets - 1].push_back(num);
            continue;
        }
        buckets[bucketIndex].push_back(num);
    }

    for (int i = 0; i < n_buckets; i++)
    {
        if (!buckets[i].empty())
        {
            insertion_sort(buckets[i]);
        }
    }

    std::vector<int> sorted_nums;
    for (const auto &bucket : buckets)
    {
        sorted_nums.insert(sorted_nums.end(), bucket.begin(), bucket.end());
    }

    return sorted_nums;
}

int main(int argc, char const *argv[])
{
    if(argc < 3){
        std::cout<< "número de parametros insuficientes\n";
        std::exit(1);
    }

    std::string filename = argv[1];
    std::string type_sorting = argv[2];

    std::fstream file(filename);
    std::fstream ordened("out.txt", std::ios::out | std::ios::trunc);
    std::vector<int> nums;
    int n;
    int maior = INT_MIN;
    int menor = INT_MAX;

    while (file >> n)
    {
        nums.push_back(n);
        if (n > maior)
            maior = n;
        if (n < menor)
            menor = n;
    }
    if (type_sorting == "B")
    {
        int n_buckets = std::stoi(argv[3]);
        nums = bucket_sort(n_buckets, nums, menor, maior);
    }
    else if (type_sorting == "I")
        nums = insertion_sort(nums);
    else
        {
            std::cout << "Modo de ordenação inválido escolha I ou B\n";
            std::exit(1);
        }
    // Parte irrelevante, apenas para conferir se o resultado está correto;
    std::cout << menor << " " << maior << std::endl;
    for (int i = 0; i < nums.size(); i++)
        ordened << nums[i] << "\n";

    return 0;
}
