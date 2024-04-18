Program gestionnaire_de_transaction;
Uses
Wincrt, Windows, SysUtils, Math;
Const
  MAX_CLIENTS = 100;
  MAX_TRANSACTIONS = 100;
Type
  Transaction = Record
    TypeTransaction: String[50];
    Montant: Real;
    SoldeApresTransaction: Real;
  End;
  Client = Record
    nom: String[50];
    prenom: String[50];
    ID: String[50];
    MDPS: String[50];
    solde: Real;
    NumCompte: Integer;
    Transactions: Array[1..MAX_TRANSACTIONS] Of Transaction;
    NbTransactions: Integer;
  End;
  TClient = Array[1..MAX_CLIENTS] Of Client;
Var
  ch: Integer;
  clients: TClient;
  nbClient: Integer;
  //--------------------------------------------------------------------------------------------

(*Procedure BeepOnKeyPress;
var
  Key: Char;
begin
  while True do
  begin
    // Check if a key is pressed
    if KeyPressed then
    begin
      // Read the pressed key
      Key := ReadKey;
      // Play a beep sound
      Windows.Beep(1000, 100); // You can adjust the frequency and duration of the beep
      // Echo the pressed key
      Write(Key);
    end;
    // Delay to control the frequency of checking for key presses
    Delay(10);
  end;
end;*)
  //--------------------------------------------------------------------------------------------
Procedure ChangeBackgroundColor(color: Byte);
//procedure pour que la couleur fond terminal d'exection soit toujours noir
Begin
  TextBackground(color);
  Clrscr;
  //vider l'ecran du terminal pour ne laisser que la couleur demandé
End;
//--------------------------------------------------------------------------------------------
Function ReadPassword: String;
Var
  Key: Char;
  Password: String;
Begin
  Password := '';
  Repeat
    Key := Readkey;
    If (Key <> #13) And (Key <> #8) Then
      Begin
        Write('*');
        Password := Password + Key;
      End
    Else If Key = #8 Then
           Begin
             If Length(Password) > 0 Then
               Begin
                 Delete(Password, Length(Password), 1);
                 Write(#8, ' ', #8);
               End;
           End;
  Until Key = #13;
  Writeln;
  ReadPassword := Password;
End;
//--------------------------------------------------------------------------------------------

Procedure AddClient;
Begin
  Writeln('AUTHENTIFICATION....');
  With clients[nbClient + 1] Do
    Begin
      Write('Nom: ');
      Readln(nom);
      Write('Prénom: ');
      Readln(prenom);
      Write('Identifiant: ');
      Readln(ID);
      Write('Mot de passe: ');
      MDPS := ReadPassword;
      Write('Solde initial: ');
      Readln(solde);
      Inc(nbClient);
      NbTransactions := 0;
    End;
End;
//--------------------------------------------------------------------------------------------

Procedure AfficheINFO;
Begin
  With clients[nbClient] Do
    Begin
      Writeln('Informations du nouveau client :');
      Writeln('Nom: ', nom);
      Writeln('Prénom: ', prenom);
      Writeln('Identifiant: ', ID);
      Writeln('Mot de passe: ', MDPS);
      Writeln('Solde initial: ', solde:0:2, ' DA');
    End;
End;
//--------------------------------------------------------------------------------------------

Procedure AjouterTransaction(clientIndex: Integer; TypeTransaction: String; Montant: Real);
Begin
  clients[clientIndex].NbTransactions := clients[clientIndex].NbTransactions + 1;
  With clients[clientIndex].Transactions[clients[clientIndex].NbTransactions] Do
    Begin
      TypeTransaction := TypeTransaction;
      Montant := Montant;
      SoldeApresTransaction := clients[clientIndex].solde + Montant;
    End;
  clients[clientIndex].solde := clients[clientIndex].solde + Montant;
End;
//--------------------------------------------------------------------------------------------

Procedure Depot(clientIndex: Integer);
Var
  Montant: Real;
Begin
  Write('Veuillez préciser le montant à déposer : ');
  Readln(Montant);
  Writeln('Veuillez patienter...');
  sleep(4000);
  Writeln('Nous traitons votre demande....');
  sleep(3000);
  With clients[clientIndex] Do
    Begin
      NbTransactions := NbTransactions + 1;
      Transactions[NbTransactions].TypeTransaction := 'Dépôt';
      Transactions[NbTransactions].Montant := Montant;
      Transactions[NbTransactions].SoldeApresTransaction := solde + Montant;
      solde := solde + Montant;
    End;
  Clrscr;
  Writeln('--------------------------*Youb Nader*--------------------------');
  Writeln('Dépôt effectué avec succès');
  Writeln('Compte: ', clients[nbClient].nom, ' ', clients[nbClient].prenom);
  Writeln('Type de transaction: dépôt d''argent');
  Writeln('Montant déposé: ', Montant:0:2, ' DA');
  Writeln('Nouveau solde: ', clients[clientIndex].solde:0:2, ' DA');
  Writeln('-----------------------*Bonne journée*-----------------------');
End;
//--------------------------------------------------------------------------------------------

Procedure AfficheHistorique(clientI: Integer);
Var
  i: Integer;
Begin
  With clients[clientI] Do
    Begin
      For i := 1 To NbTransactions Do
        Begin
          Writeln('Transaction ', i, ': ');
          Writeln('Compte: ', clients[nbClient].nom, ' ', clients[nbClient].prenom);
          Writeln('Type de transaction: ', Transactions[i].TypeTransaction);
          Writeln('Montant: ', Transactions[i].Montant:0:2, ' DA');
          Writeln('Solde après la transaction: ', Transactions[i].SoldeApresTransaction:0:2, ' DA')
          ;
          Writeln('-------------------------------------------------------------------------');
        End;
    End;
End;
//--------------------------------------------------------------------------------------------
Procedure ConsultationSolde(clientI: Integer);
Begin
  Writeln('Compte: ', clients[nbClient].nom, ' ', clients[nbClient].prenom);
  Writeln('Solde actuel : ', clients[clientI].solde:0:2, ' DA');
End;
//--------------------------------------------------------------------------------------------

Procedure menu;
Var
  ch, cch: Integer;
  montant: Real;
Begin
  Repeat
    Writeln('---------------MENU---------------');
    Writeln('1: Transaction');
    Writeln('2: Historique de transaction');
    Writeln('3: Consultation de solde');
    Writeln('4: Quitter');
    Write('Veillez entrer votre choix: ');
    Readln(ch);
  Until (ch >= 1) And (ch <= 4);
  Case ch Of
    1:
       Begin
         Repeat
           Clrscr;
           Writeln('--------------------------*Youb Nader*--------------------------');
           Writeln('TRANSACTION....');
           Writeln('1: Retrait d''argent');
           Writeln('2: Dépôt d''argent');
           Write('Veuillez définir le type de transaction: ');
           Readln(cch);
         Until (cch >= 1) And (cch <= 2);
         Case cch Of
           1:
              Begin
                Writeln('----------------------------------------------------------');
                Writeln('Retrait....');
                Write('Veillez préciser le montant à retirer: ');
                Readln(montant);
                Writeln('Veuillez patienter...');
                sleep(4000);
                Writeln('Nous traitons votre demande....');
                sleep(3000);
                If (montant > clients[nbClient].solde) Then
                  Begin
                    Clrscr;
                    Writeln('--------------------------*Youb Nader*--------------------------');
                    Writeln('Solde insuffisant.');
                    Writeln('-----------------------*Bonne journée*-----------------------');
                  End
                Else
                  Begin
                    clients[nbClient].solde := clients[nbClient].solde - montant;
                    Inc(clients[nbClient].NbTransactions);
                    clients[nbClient].Transactions[clients[nbClient].NbTransactions].TypeTransaction
                    := 'Retrait';
                    clients[nbClient].Transactions[clients[nbClient].NbTransactions].Montant :=

                                                                                             montant
                    ;
                    clients[nbClient].Transactions[clients[nbClient].NbTransactions].
                    SoldeApresTransaction := clients[nbClient].solde;
                    Clrscr;
                    Writeln('--------------------------*Youb Nader*--------------------------');
                    Writeln('Retrait effectué avec succès');
                    Writeln('Compte: ', clients[nbClient].nom, ' ', clients[nbClient].prenom);
                    Writeln('Type de transaction: retrait');
                    Writeln('Montant retiré: ', montant:0:2, ' DA');
                    Writeln('Nouveau solde: ', clients[nbClient].solde:0:2, ' DA');
                    Writeln('----------------------*Bonne journée*-----------------------');
                  End;
              End;
           2:
              Begin
                Clrscr;
                Writeln('--------------------------*Youb Nader*--------------------------');
                Writeln('Dépôt....');
                Depot(nbClient);
              End;
         End;
       End;
    2:
       Begin
         Clrscr;
         Writeln('--------------------------*Youb Nader*--------------------------');
         Writeln('Historique de transaction....');
         Writeln('-------------------------------------------------------------');
         Writeln('Veuillez patienter...');
         sleep(4000);
         Writeln('Nous traitons votre demande....');
         sleep(3000);
         Clrscr;
         Writeln('--------------------------*Youb Nader*--------------------------');
         Writeln('Historique de transaction....');
         Writeln('-------------------------------------------------------------');
         AfficheHistorique(nbClient);
         Readln;
       End;
    3:
       Begin
         Clrscr;
         Writeln('--------------------------*Youb Nader*--------------------------');
         Writeln('consultation du solde....');
         Writeln('Veuillez patienter...');
         sleep(4000);
         Writeln('Nous traitons votre demande...');
         sleep(3000);
         Clrscr;
         Writeln('--------------------------*Youb Nader*--------------------------');
         Writeln('consultation du solde....');
         ConsultationSolde(nbClient);
         Writeln('-------------------------------------------------------------');
       End;
    4:
       Begin
         Clrscr;
         Writeln('--------------------------*Youb Nader*--------------------------');
         Writeln('Merci de nous avoir fait confiance');
         Writeln('-----------------------*Bonne journée*-----------------------');
         Exit;
       End;
  End;
End;
//--------------------------------------------------------------------------------------------
Begin
  ChangeBackgroundColor(0);
  TextColor(White);
  Writeln('--------------------------*Youb Nader*--------------------------');
  AddClient;
  Writeln('Authentification en cours....');
  Sleep(5000);
  Clrscr;
  Writeln('--------------------------*Youb Nader*--------------------------');
  Writeln('Authentification effectuée avec succès.');
  AfficheINFO;
  Writeln('-------------------------------------------------------------');
  Readln;
  Repeat
    menu;
    Readln;
  Until Readkey = Chr(27);
End.