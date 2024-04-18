Program couleur_terminal;
Uses Wincrt;
//-----------------------------------------------------------------------------

Procedure ChangeBackgroundColor(color: Byte);
//procedure pour que la couleur fond terminal d'exection soit toujours noir             //youb nader
Begin
  TextBackground(color);
  Clrscr;
  //vider l'ecran du terminal pour ne laisser que la couleur demandé
End;
//---------------------------------------------------------------------------
Begin
  ChangeBackgroundColor(0);

(*vous devez appeler la procedure avant d'ecrire la 1ère ligne de code
	(optionel) j'ai mis 0 parceque c'est le code de la couleur noir mais vous pouvez le changer*)
  textcolor(white);

(*si vous avez choisis la couleur du backgroung noir alors le text est plus lisible avec la couleur blanche
	ce qui peut se faire seulement avec la fonction "textcolor()"*)
  Writeln('hello');
  Readln;
End.
