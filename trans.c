// transfer money between accounts
void transferMoney(FILE *fPtr)
{
    unsigned int senderAcc, receiverAcc;
    double amount;

    struct clientData sender = {0, "", "", 0.0};
    struct clientData receiver = {0, "", "", 0.0};

    printf("Enter sender account number: ");
    scanf("%u", &senderAcc);

    printf("Enter receiver account number: ");
    scanf("%u", &receiverAcc);

    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);

    // read sender account
    fseek(fPtr,
          (senderAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&sender,
          sizeof(struct clientData),
          1,
          fPtr);

    // read receiver account
    fseek(fPtr,
          (receiverAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&receiver,
          sizeof(struct clientData),
          1,
          fPtr);

    // validations
    if (sender.acctNum == 0)
    {
        printf("Sender account not found.\n");
        return;
    }

    if (receiver.acctNum == 0)
    {
        printf("Receiver account not found.\n");
        return;
    }

    if (sender.balance < amount)
    {
        printf("Insufficient balance.\n");
        return;
    }

    // transfer
    sender.balance -= amount;
    receiver.balance += amount;

    // update sender
    fseek(fPtr,
          (senderAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&sender,
           sizeof(struct clientData),
           1,
           fPtr);

    // update receiver
    fseek(fPtr,
          (receiverAcc - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&receiver,
           sizeof(struct clientData),
           1,
           fPtr);

    printf("Money transferred successfully.\n");

    printf("Sender New Balance   : %.2lf\n", sender.balance);
    printf("Receiver New Balance : %.2lf\n", receiver.balance);
}