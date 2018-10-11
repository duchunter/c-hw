#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  each route is represented by a linked-list, the id of the first
  and end element is the same and equal to 0
*/
typedef struct Node {
  int id;
  int x;
  int y;
  double distance;
  int load;

  struct Node* next;
  struct Node* prev;
} Node;

// Create new node
Node *newNode(int id, int x, int y, double distance, int load) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->id = id;
  new->x = x;
  new->y = y;
  new->distance = distance;
  new->load = load;

  new->prev = NULL;
  new->next = NULL;
  return new;
}

// Calculate distance between 2 nodes
double getDistance(Node* a, Node* b) {
  double x = a->x - b->x;
  double y = a->y - b->y;
  return sqrt(x * x + y * y);
}

typedef struct RoutePlan {
  // array of pointers, each pointer points the the first element of a route
  Node** starts;
  int size; // number of routes
} RoutePlan;

// Create new plan
RoutePlan *newPlan(int size) {
  RoutePlan *new = (RoutePlan *) malloc(sizeof(RoutePlan));
  new->size = size;
  new->starts = (Node **) malloc(size * sizeof(Node*));
  return new;
}

// Print a single route
void printRoute(Node* start) {
  Node* cur = start;
  while (cur != NULL) {
    printf(
      "id: %d\tx: %d\ty: %d\tdistance: %.2lf\tload: %d\n",
      cur->id, cur->x, cur->y, cur->distance, cur->load
    );

    cur = cur->next;
  }

  return;
}

// Print a route plan
void printPlan(RoutePlan* rp) {
  for (int i = 0; i < rp->size; i++) {
    printf("- Route %d:\n", i + 1);
    printRoute((rp->starts)[i]);
  }

  return;
}

// Split route into 2 (?)
RoutePlan* split(Node* start, int id1, int id2) {
  RoutePlan *plan = newPlan(2);
  (plan->starts)[0] = start;
  Node *cur = start;
  Node *head = NULL;
  Node *tail = NULL;

  // Traverse input route to find head and tail of second route
  while (cur != NULL) {
    // Mark head of the second route
    if (cur->id == id1) {
      head = cur;
    }

    // Mark tail of the second route
    if (cur->id == id2) {
      tail = cur;
    }

    cur = cur->next;
  }

  // Swap head and tail if needed
  if (head->load < tail->load) {
    cur = head;
    head = tail;
    tail = cur;
  }

  // Cut second route from input route
  (head->prev)->next = tail->next;

  // Calculate total load reduced
  int diff = head->load - tail->load;
  if (diff == 0) {
    diff = head->load - head->next->load;
  }

  // Reduce total load from first route
  int total = start->load;
  for (cur = start; cur != NULL; cur = cur->next) {
    cur->load -= diff;
    if (cur->id == head->prev->id) break;
  }

  head->prev = NULL;
  tail->next = NULL;

  // Reduce total load from second route
  int diff2 = head->load - diff;
  for (cur = head; cur != NULL; cur = cur->next) {
    cur->load -= diff2;
  }

  // Add 2 0s node to head and tail to create a new route
  Node *new = newNode(0, 0, 0, 0, diff);
  new->next = head;
  head->prev = new;

  (plan->starts)[1] = new;

  new = newNode(0, 0, 0, 0, 0);
  tail->next = new;
  new->prev = tail;

  return plan;
}

// Create a route from file
Node* createSingleRoute(char* filename) {
  // First node of a route is always 0
  Node* root = newNode(0, 0, 0, 0, 0);
  Node* cur = root;
  Node* new = NULL;

  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printf("Cannot open %s\n", filename);
    return NULL;
  }

  // Scan number of client and eliminate first 0s line
  int id, x, y, load, clients, totalLoad = 0;
  fscanf(f, "%d", &clients);
  fscanf(f, "%d", &id);
  fscanf(f, "%d", &x);
  fscanf(f, "%d", &y);

  // Scan all other node and push into list
  for (int i = 0; i < clients; i++) {
    fscanf(f, "%d", &id);
    fscanf(f, "%d", &x);
    fscanf(f, "%d", &y);
    fscanf(f, "%d", &load);

    // Save total load
    totalLoad += load;

    // Create new node and append to route
    new = newNode(id, x, y, 0, load);
    cur->next = new;
    new->prev = cur;
    cur = cur->next;
    cur->distance = getDistance(root, cur);
  }

  // Reduce total load each node
  for (Node *temp = root; temp != NULL; temp = temp->next) {
    load = temp->load;
    temp->load = totalLoad;
    totalLoad -= load;
  }

  // Append last node (0)
  new = newNode(0, 0, 0, 0, 0);
  cur->next = new;
  new->prev = cur;

  // Close file and return route
  fclose(f);
  return root;
}

int main() {
  printf("Start\n");
  Node* initRoute = createSingleRoute("route.txt");
  printRoute(initRoute);

  printf("Split from 2 to 6\n");
  RoutePlan* plan = split(initRoute, 1, 1);
  printPlan(plan);

  return 0;
}
