// c++程序设计：物品库存管理
// 免责声明：这是一个示例程序，可能不正确或不完整
// 请根据你的需求和规范检查和修改它

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// 定义一个结构体表示品牌
struct Brand {
    string name; // 品牌名称
    int quantity; // 品牌数量
    double price; // 品牌价格
};

// 定义一个结构体表示商品品种
struct Product {
    string code; // 商品品种代码
    string description; // 商品品种描述
    int num_brands; // 商品品种包含的品牌数量
    Brand brands[10]; // 品牌数组，最多10个
    Product *next; // 指向链表中下一个商品品种的指针
};

// 定义一个类表示库存
class Inventory {
private:
    Product *head; // 指向链表头部的指针
public:
    Inventory(); // 构造函数
    ~Inventory(); // 析构函数
    void readFromFile(string filename); // 从文件中读取数据并创建链表
    void writeToFile(string filename); // 将链表中的数据写入文件中
    void addProduct(); // 向链表中添加一个新的商品品种
    void deleteProduct(); // 从链表中删除一个商品品种
    Product* searchProduct(); // 根据商品品种代码查找一个商品品种
    void displayProduct(); // 显示一个商品品种的信息
    void displayAll(); // 显示所有商品品种的信息
    void inputOutput(string in_file, string out_file); // 读取进出货文件并输出统计表
};

// 构造函数，初始化链表为空
Inventory::Inventory() {
    head = NULL;
}

// 析构函数，释放链表中的内存空间
Inventory::~Inventory() {
    Product *p = head; // 用一个指针p遍历链表
    while (p != NULL) {
        Product *q = p->next; // 用一个指针q保存p的下一个节点
        delete p; // 删除p指向的节点
        p = q; // p指向下一个节点
    }
}

// 从文件中读取数据并创建链表
void Inventory::readFromFile(string filename) {
    ifstream fin(filename); // 打开文件输入流
    if (!fin) { // 如果打开失败，输出错误信息并返回
        cout << "无法打开文件" << filename << endl;
        return;
    }
    while (!fin.eof()) { // 当没有到达文件末尾时，循环读取数据
        Product *p = new Product; // 创建一个新的商品品种节点
        fin >> p->code >> p->description >> p->num_brands; // 读取商品品种代码，描述和品牌数量
        for (int i = 0; i < p->num_brands; i++) { // 循环读取每个品牌的信息
            fin >> p->brands[i].name >> p->brands[i].quantity >> p->brands[i].price; // 读取品牌名称，数量和价格
        }
        p->next = NULL; // 将新节点的next指针设为NULL
        if (head == NULL) { // 如果链表为空，将新节点设为头节点
            head = p;
        } else { // 如果链表不为空，将新节点插入到合适的位置，保持按照商品品种代码的顺序排列
            Product *q = head; // 用一个指针q遍历链表，找到插入位置的前一个节点
            Product *r = NULL; // 用一个指针r保存q的前一个节点，初始为NULL
            while (q != NULL && q->code < p->code) { // 当q不为空且q的商品品种代码小于p的商品品种代码时，继续往后找
                r = q; // r指向q
                q = q->next; // q指向下一个节点
            }
            if (r == NULL) { // 如果r为空，说明新节点应该插入到头部
                p->next = head; // 将新节点的next指针指向原来的头节点
                head = p; // 将新节点设为头节点
            } else { // 如果r不为空，说明新节点应该插入到r和q之间
                r->next = p; // 将r的next指针指向新节点
                p->next = q; // 将新节点的next指针指向q
            }
        }
    }
    fin.close(); // 关闭文件输入流
}

// 将链表中的数据写入文件中
void Inventory::writeToFile(string filename) {
    ofstream fout(filename); // 打开文件输出流
    if (!fout) { // 如果打开失败，输出错误信息并返回
        cout << "无法打开文件" << filename << endl;
        return;
    }
    Product *p = head; // 用一个指针p遍历链表
    while (p != NULL) { // 当p不为空时，循环写入数据
        fout << p->code << " " << p->description << " " << p->num_brands << endl; // 写入商品品种代码，描述和品牌数量
        for (int i = 0; i < p->num_brands; i++) { // 循环写入每个品牌的信息
            fout << p->brands[i].name << " " << p->brands[i].quantity << " " << p->brands[i].price << endl; // 写入品牌名称，数量和价格
        }
        p = p->next; // p指向下一个节点
    }
    fout.close(); // 关闭文件输出流
}

// 向链表中添加一个新的商品品种
void Inventory::addProduct() {
    Product *p = new Product; // 创建一个新的商品品种节点
    cout << "请输入商品品种代码：" << endl; // 提示用户输入商品品种代码
    cin >> p->code; // 读取用户输入的商品品种代码
    cout << "请输入商品品种描述：" << endl; // 提示用户输入商品品种描述
    cin >> p->description; // 读取用户输入的商品品种描述
    cout << "请输入商品品种包含的品牌数量：" << endl; // 提示用户输入商品品种包含的品牌数量
    cin >> p->num_brands; // 读取用户输入的商品品种包含的品牌数量
    for (int i = 0; i < p->num_brands; i++) { // 循环读取每个品牌的信息
        cout << "请输入第" << i + 1 << "个品牌的名称：" << endl; // 提示用户输入第i+1个品牌的名称
        cin >> p->brands[i].name; // 读取用户输入的第i+1个品牌的名称
        cout << "请输入第" << i + 1 << "个品牌的数量：" << endl; // 提示用户输入第i+1个品牌的数量
        cin >> p->brands[i].quantity; // 读取用户输入的第i+1个品牌的数量
        cout << "请输入第" << i + 1 << "个品牌的价格：" << endl; // 提示用户输入第i+1个品牌的价格
        cin >> p->brands[i].price; // 读取用户输入的第i+1个品牌的价格
    }
    p->next = NULL; // 将新节点的next指针设为NULL
    if (head == NULL) { // 如果链表为空，将新节点设为头节点
        head = p;
    } else { // 如果链表不为空，将新节点插入到合适的位置，保持按照商品品种代码的顺序排列
        Product *q = head; // 用一个指针q遍历链表，找到插入位置的前一个节点
        Product *r = NULL; // 用一个指针r保存q的前一个节点，初始为NULL
        while (q != NULL && q->code < p->code) { // 当q不为空且q的商品品种代码小于p的商品品种代码时，继续往后找
            r = q; // r指向q
            q = q->next; // q指向下一个节点
        }
        if (r == NULL) { // 如果r为空，说明新节点应该插入到头部
            p->next = head; // 将新节点的next指针指向原来的头节点
            head = p; // 将新节点设为头节点
        } else { // 如果r不为空，说明新节点应该插入到r和q之间
            r->next = p; // 将r的next指针指向新节点
            p->next = q; // 将新节点的next指针指向q
        }
    }
    cout << "添加成功！" << endl; // 输出添加成功的信息
}

// 从链表中删除一个商品品种
void Inventory::deleteProduct() {
    cout << "请输入要删除的商品品种代码：" << endl; // 提示用户输入要删除的商品品种代码
    string code; // 定义一个字符串变量code存储用户输入的商品品种代码
    cin >> code; // 读取用户输入的商品品种代码
    Product *p = head; // 用一个指针p遍历链表，找到要删除的节点
    Product *q = NULL; // 用一个指针q保存p的前一个节点，初始为NULL
    while (p != NULL && p->code != code) { // 当p不为空且p的商品品种代码不等于用户输入的商品品种代码时，继续往后找
        q = p; // q指向p
        p = p->next; // p指向下一个节点
    }
    if (p == NULL) { // 如果p为空，说明没有找到要删除的节点，输出错误信息并返回
        cout << "没有找到该商品品种！" << endl;
        return;
    }
    if (q == NULL) { // 如果q为空，说明要删除的节点是头节点
        head = p->next; // 将头节点设为p的下一个节点
    } else { // 如果q不为空，说明要删除的节点不是头节点
        q->next = p->next; // 将q的next指针指向p的下一个节点
    }
    delete p; // 删除p指向的节点
    cout << "删除成功！" << endl; // 输出删除成功的信息
}

// 根据商品品种代码查找一个商品品种
Product* Inventory::searchProduct() {
    cout << "请输入要查找的商品品种代码：" << endl; // 提示用户输入要查找的商品品种代码
    string code; // 定义一个字符串变量code存储用户输入的商品品种代码
    cin >> code; // 读取用户输入的商品品种代码
    Product *p = head; // 用一个指针p遍历链表，找到要查找的节点
    while (p != NULL && p->code != code) { // 当p不为空且p的商品品种代码不等于用户输入的商品品种代码时，继续往后找
        p = p->next; // p指向下一个节点
    }
    if (p == NULL) { // 如果p为空，说明没有找到要查找的节点，输出错误信息并返回NULL
        cout << "没有找到该商品品种！" << endl;
        return NULL;
    }
    return p; // 返回p指向的节点
}
// 显示一个商品品种的信息
void Inventory::displayProduct() {
    Product *p = searchProduct(); // 调用searchProduct函数，返回要显示的商品品种节点
    if (p == NULL) { // 如果返回的节点为空，说明没有找到要显示的商品品种，直接返回
        return;
    }
    cout << "商品品种代码：" << p->code << endl; // 输出商品品种代码
    cout << "商品品种描述：" << p->description << endl; // 输出商品品种描述
    cout << "商品品种包含的品牌数量：" << p->num_brands << endl; // 输出商品品种包含的品牌数量
    for (int i = 0; i < p->num_brands; i++) { // 循环输出每个品牌的信息
        cout << "第" << i + 1 << "个品牌的名称：" << p->brands[i].name << endl; // 输出第i+1个品牌的名称
        cout << "第" << i + 1 << "个品牌的数量：" << p->brands[i].quantity << endl; // 输出第i+1个品牌的数量
        cout << "第" << i + 1 << "个品牌的价格：" << p->brands[i].price << endl; // 输出第i+1个品牌的价格
    }
}

// 显示所有商品品种的信息
void Inventory::displayAll() {
    Product *p = head; // 用一个指针p遍历链表
    while (p != NULL) { // 当p不为空时，循环显示每个商品品种的信息
        cout << "商品品种代码：" << p->code << endl; // 输出商品品种代码
        cout << "商品品种描述：" << p->description << endl; // 输出商品品种描述
        cout << "商品品种包含的品牌数量：" << p->num_brands << endl; // 输出商品品种包含的品牌数量
        for (int i = 0; i < p->num_brands; i++) { // 循环输出每个品牌的信息
            cout << "第" << i + 1 << "个品牌的名称：" << p->brands[i].name << endl; // 输出第i+1个品牌的名称
            cout << "第" << i + 1 << "个品牌的数量：" << p->brands[i].quantity << endl; // 输出第i+1个品牌的数量
            cout << "第" << i + 1 << "个品牌的价格：" << p->brands[i].price << endl; // 输出第i+1个品牌的价格
        }
        p = p->next; // p指向下一个节点
    }
}

// 读取进出货文件并输出统计表
void Inventory::inputOutput(string in_file, string out_file) {
    ifstream fin(in_file); // 打开进货文件输入流
    ofstream fout(out_file); // 打开出货文件输出流
    if (!fin || !fout) { // 如果打开失败，输出错误信息并返回
        cout << "无法打开文件" << in_file << "或" << out_file << endl;
        return;
    }
    fout << "出货清单：" << endl; // 输出出货清单的标题
    fout << "时间\t\t商品品种描述\t\t具体品牌\t\t出货数量\t\t总价格" << endl; // 输出出货清单的表头
    while (!fin.eof()) { // 当没有到达进货文件末尾时，循环读取数据
        string code; // 定义一个字符串变量code存储商品品种代码
        string name; // 定义一个字符串变量name存储品牌名称
        int quantity; // 定义一个整数变量quantity存储进出货数量，正数表示进货，负数表示出货
        fin >> code >> name >> quantity; // 读取商品品种代码，品牌名称和进出货数量
        Product *p = head; // 用一个指针p遍历链表，找到对应的商品品种节点
        while (p != NULL && p->code != code) { // 当p不为空且p的商品品种代码不等于读取的商品品种代码时，继续往后找
            p = p->next; // p指向下一个节点
        }
        if (p == NULL) { // 如果p为空，说明没有找到对应的商品品种，输出错误信息并跳过这条数据
            cout << "没有找到商品品种" << code << "！" << endl;
            continue;
        }
        int i; // 定义一个整数变量i存储品牌在商品品种中的索引
        for (i = 0; i < p->num_brands; i++) { // 循环查找对应的品牌
            if (p->brands[i].name == name) { // 如果找到对应的品牌，跳出循环
                break;
            }
        }
        if (i == p->num_brands) { // 如果没有找到对应的品牌，输出错误信息并跳过这条数据
            cout << "没有找到品牌" << name << "！" << endl;
            continue;
        }
        if (quantity > 0) { // 如果进出货数量大于0，表示进货
            p->brands[i].quantity += quantity; // 增加品牌的数量
        } else if (quantity < 0) { // 如果进出货数量小于0，表示出货
            if (p->brands[i].quantity + quantity < 0) { // 如果出货数量超过库存数量，输出错误信息并跳过这条数据
                cout << "出货数量超过库存数量！" << endl;
                continue;
            }
            p->brands[i].quantity += quantity; // 减少品牌的数量
            time_t t = time(NULL); // 获取当前时间
            char s[20]; // 定义一个字符数组s存储时间字符串
            strftime(s, 20, "%Y-%m-%d %H:%M:%S", localtime(&t)); // 将时间格式化为字符串
            fout << s << "\t" << p->description << "\t\t" << p->brands[i].name << "\t\t" << -quantity << "\t\t" << -quantity * p->brands[i].price << endl; // 输出出货清单的一行数据，包括时间，商品品种描述，具体品牌，出货数量和总价格
        } else { // 如果进出货数量等于0，跳过这条数据
            continue;
        }
    }
    fin.close(); // 关闭进货文件输入流
    fout.close(); // 关闭出货文件输出流
}

// 主函数
int main() {
    Inventory inv; // 创建一个库存对象inv
    inv.readFromFile("inventory.txt"); // 从文件中读取数据并创建链表
    int choice; // 定义一个整数变量choice存储用户的选择
    do {
        cout << "请选择要执行的操作：" << endl; // 输出菜单选项
        cout << "1. 添加商品品种" << endl;
        cout << "2. 删除商品品种" << endl;
        cout << "3. 查找商品品种" << endl;
        cout << "4. 显示商品品种" << endl;
        cout << "5. 显示所有商品品种" << endl;
        cout << "6. 读取进出货文件并输出统计表" << endl;
        cout << "0. 退出程序" << endl;
        cin >> choice; // 读取用户的选择
        switch (choice) { // 根据用户的选择执行相应的操作
            case 1: // 如果用户选择1，调用addProduct函数，添加一个新的商品品种
                inv.addProduct();
                break;
            case 2: // 如果用户选择2，调用deleteProduct函数，删除一个商品品种
                inv.deleteProduct();
                break;
            case 3: // 如果用户选择3，调用searchProduct函数，查找一个商品品种
                inv.searchProduct();
                break;
            case 4: // 如果用户选择4，调用displayProduct函数，显示一个商品品种的信息
                inv.displayProduct();
                break;
            case 5: // 如果用户选择5，调用displayAll函数，显示所有商品品种的信息
                inv.displayAll();
                break;
            case 6: // 如果用户选择6，调用inputOutput函数，读取进出货文件并输出统计表
                inv.inputOutput("input.txt", "output.txt");
                break;
            case 0: // 如果用户选择0，退出程序
                cout << "感谢使用本程序！" << endl;
                break;
            default: // 如果用户选择其他无效的选项，输出错误信息
                cout << "无效的选项！" << endl;
                break;
        }
    } while (choice != 0); // 当用户没有选择退出时，循环执行菜单选项
    inv.writeToFile("inventory.txt"); // 将链表中的数据写入文件中
    return 0; // 返回0表示程序正常结束
}
