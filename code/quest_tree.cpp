#include <stdlib.h>

struct qnode;
struct s_quest;

enum qnode_type
{
    PROGRESS,
    END
};

struct qnode
{
    s_quest* quest;
    int type;

    int num_next_nodes;
    qnode** next_nodes;

    qnode* prev_node;
};

qnode* new_node(qnode* prev, int type)
{
    if(prev == nullptr || prev->type == END)
    {
        return nullptr;
    }

    s_quest* quest = prev->quest;
    if(quest == nullptr)
    {
        return nullptr;
    }

    qnode* node = (qnode*) malloc(sizeof(qnode));
    *node = {0};

    node->quest = quest;
    node->type = type;
    node->prev_node = prev;
    
    qnode** temp_prev_next_nodes = (qnode**) realloc(prev->next_nodes, prev->num_next_nodes + 1);
    if(temp_prev_next_nodes == nullptr)
    {
        //destroy_quest??
        free(prev->next_nodes);
        free(node);
        return nullptr;
    }

    prev->next_nodes = temp_prev_next_nodes;
    prev->next_nodes[prev->num_next_nodes] = node;
    prev->num_next_nodes += 1;

    if(type == END)
    {
        qnode** temp_quest_all_endings = (qnode**) realloc(quest->all_endings, quest->num_all_endings + 1);
        if(temp_quest_all_endings == nullptr)
        {
            free(quest->all_endings);
            return nullptr;
        }

        quest->all_endings = temp_quest_all_endings;
        quest->all_endings[quest->num_all_endings] = node;
        quest->num_all_endings += 1;
    }

    qnode** temp_quest_all_nodes = (qnode**) realloc(quest->all_nodes, quest->num_all_nodes + 1);
    if(temp_quest_all_nodes == nullptr)
    {
        free(quest->all_nodes);
        return nullptr;
    }

    quest->all_nodes = temp_quest_all_nodes;
    quest->all_nodes[quest->num_all_nodes] = node;
    quest->num_all_nodes += 1;

    return node;
}

void destroy_node(qnode* node)
{
    //oooof
}

struct s_quest
{
    qnode first_node;

    int num_all_endings;
    qnode** all_endings;

    int num_all_nodes;
    qnode** all_nodes;
};

s_quest* new_quest()
{
    s_quest* quest = (s_quest*) malloc(sizeof(s_quest));
    *quest = {0};

    quest->first_node.quest = quest;

    return quest;
}

void destroy_quest(s_quest* quest)
{
    

    free(quest);
}

int main()
{
    s_quest* my_quest = new_quest();
    
    qnode* task_1 = &(my_quest->first_node);
        qnode* task_2 = new_node(task_1, PROGRESS);
            qnode* task_3 = new_node(task_2, PROGRESS);
                qnode* task_4 = new_node(task_3, END);
            qnode* task_4 = new_node(task_2, END);

    destroy_quest(my_quest);
    return 0;
}