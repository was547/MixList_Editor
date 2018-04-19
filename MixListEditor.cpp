#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, char*argv[])
{
	memset(&MixData, 0, sizeof(npcCompleto));

	setlocale(LC_ALL, "Portuguese");
	SetConsoleTitleA("MIXLIST");

	printf("## Conversor de MixList by 'WOZ\n\n");
	
	int opt = -1;
	printf("DIGITE O QUE VOCE DESEJA:\n1- BIN -> CSV\n2- CSV -> BIN\n\n>> ");
	scanf("%d", &opt);

	char msg[256];
	sprintf(msg, "SELECIONOU %d\n\n", opt);

	bool retn = false;

	if (opt == 1)
	{
		retn = Bin2Csv();

		if (retn)
			MessageBoxA(NULL, "Sucesso!", "Conversor", MB_OK);
		else
			MessageBoxA(NULL, "Erro!", "Conversor", MB_OK);
	}
	else if (opt == 2)
	{
		retn = Csv2Bin();

		if (retn)
			MessageBoxA(NULL, "Arquivo Mixlist_convertido.bin gerado com sucesso!", "Conversor", MB_OK);
		else
			MessageBoxA(NULL, "Erro!", "Conversor", MB_OK);
	}
	else {
		MessageBoxA(NULL, "DIGITE 1 ou 2! TENTE NOVAMENTE!", "ERRO", MB_OK);
	}

	exit(1);
	return 0;
}


bool Csv2Bin()
{
	if (!FileExists("Mixlist.bin"))
		return false;

	MixData = GetContent();

	if (!FileExists("Mixlist_NPCS.csv"))
		return false;

	if (!FileExists("Mixlist_ITENS.csv"))
		return false;

	FILE *fileRead;

	int line = -1;

	char currentline[512];
	fopen_s(&fileRead, "Mixlist_NPCS.csv", "rb");
	
	assert(fileRead != NULL);
	//NPCS
	while (fgets(currentline, sizeof(currentline), fileRead) != NULL)
	{
		//printf(currentline);

		char cmd[256], cmd2[256];
		int value = -1;

		if (sscanf_s(currentline, "%[^=]=%d", cmd, _countof(cmd), &value) == 2)
		{
			if (strcmp(cmd, "id") == 0)
			{
				line = value;
			}
			else if (strcmp(cmd, "Face") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [1]", "Error", MB_OK);
					exit(0);
				}

				MixData.npcs[line].face = value;
			}
			else if (strcmp(cmd, "Gold") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [2]", "Error", MB_OK);
					exit(0);
				}

				MixData.npcs[line].Gold = value;
			}
			else if (strcmp(cmd, "Type") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [3]", "Error", MB_OK);
					exit(0);
				}

				MixData.npcs[line].Type = value;
			}
			else if (strcmp(cmd, "Unk20") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [4]", "Error", MB_OK);
					exit(0);
				}

				MixData.npcs[line].Unknow_20 = value;
			}
			else if (strcmp(cmd, "Unk24") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [5]", "Error", MB_OK);
					exit(0);
				}

				MixData.npcs[line].Unknow_24 = value;
			}
		}
		else if (sscanf_s(currentline, "%[^=]=%s", cmd, _countof(cmd), cmd2, _countof(cmd2)) == 2)
		{
			if (strcmp(cmd, "Item") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [6]", "Error", MB_OK);
					exit(0);
				}

				st_Item ni;
				memset(&ni, 0, sizeof(st_Item));
				int getItem = scanf(cmd2, "%d,%d,%d,%d,%d,%d,%d", 
					&ni.Index,
					&ni.EF1, &ni.EFV1,
					&ni.EF2, &ni.EFV2,
					&ni.EF3, &ni.EFV3);

				MixData.npcs[line].ItemSlot = ni;
			}
			else if (strcmp(cmd, "Map") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [7]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].MapX = X;
				MixData.npcs[line].MapY = Y;
			}
			else if (strcmp(cmd, "ItemRequire[0]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [8]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[0].Req = X;
				MixData.npcs[line].Unknow[0].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[1]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [9]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[1].Req = X;
				MixData.npcs[line].Unknow[1].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[2]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [10]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[2].Req = X;
				MixData.npcs[line].Unknow[2].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[3]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [11]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[3].Req = X;
				MixData.npcs[line].Unknow[3].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[4]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [12]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[4].Req = X;
				MixData.npcs[line].Unknow[4].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[5]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [13]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[5].Req = X;
				MixData.npcs[line].Unknow[5].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[6]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [14]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[6].Req = X;
				MixData.npcs[line].Unknow[6].Value = Y;
			}
			else if (strcmp(cmd, "ItemRequire[7]") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [15]", "Error", MB_OK);
					exit(0);
				}

				int X = 0, Y = 0;

				int getItem = scanf(cmd2, "%d,%d",
					&X, &Y);

				MixData.npcs[line].Unknow[7].Req = X;
				MixData.npcs[line].Unknow[7].Value = Y;
			}

		}
		else {
			if (strcmp(currentline, "end;") == 0)
			{
				line = -1;
			}
		}
		printf("\n");
	}

	line = -1;

	fopen_s(&fileRead, "Mixlist_NPCS.csv", "rb");

	assert(fileRead != NULL);
	//ITENS
	while (fgets(currentline, sizeof(currentline), fileRead) != NULL)
	{
		//printf(currentline);

		char cmd[256], cmd2[256];
		int value = -1;

		if (sscanf_s(currentline, "%[^=]=%d", cmd, _countof(cmd), &value) == 2)
		{
			if (strcmp(cmd, "id") == 0)
			{
				line = value;
			}
			else if (strcmp(cmd, "Req") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [16]", "Error", MB_OK);
					exit(0);
				}

				MixData.Req[line].Amount = value;
			}
			else if (strcmp(cmd, "Interval") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [17]", "Error", MB_OK);
					exit(0);
				}

				//MixData.Req[line].Interval[0] = value;
			}
			else if (strcmp(cmd, "Strdef") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [18]", "Error", MB_OK);
					exit(0);
				}

				MixData.Req[line].Strdef = value;
			}
			else if (strcmp(cmd, "Unk") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [19]", "Error", MB_OK);
					exit(0);
				}

				//MixData.Req[line].Unk = value;
			}
			else if (strcmp(cmd, "Unused") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [20]", "Error", MB_OK);
					exit(0);
				}

				MixData.Req[line].Unused = value;
			}
			else if (strcmp(cmd, "Unused2") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register [21]", "Error", MB_OK);
					exit(0);
				}

				MixData.Req[line].Unused_02 = value;
			}
		}
		else if (sscanf_s(currentline, "%[^=]=%s", cmd, _countof(cmd), cmd2, _countof(cmd2)) == 2)
		{
			if (strcmp(cmd, "Item") == 0)
			{
				if (line == -1)
				{
					MessageBoxA(NULL, "Bad file register  [22]", "Error", MB_OK);
					exit(0);
				}

				st_Item ni;
				memset(&ni, 0, sizeof(st_Item));
				int getItem = scanf(cmd2, "%d,%d,%d,%d,%d,%d,%d",
					&ni.Index,
					&ni.EF1, &ni.EFV1,
					&ni.EF2, &ni.EFV2,
					&ni.EF3, &ni.EFV3);

				MixData.Req[line].item = ni;
			}
		}
		else {
			if (strcmp(currentline, "end;") == 0)
			{
				line = -1;
			}
		}
		printf("Convertendo...\n");
	}

	FILE *m_file = NULL;

	m_file = fopen("Mixlist_convertido.bin", "wt");

	if (m_file == NULL)
	{
		return false;
	}

	fwrite(&MixData, sizeof(npcCompleto), 1, m_file);

	fclose(m_file);

	return true;
}

bool Bin2Csv()
{
	if (!FileExists("Mixlist.bin"))
		return false;

	MixData = GetContent();

	remove("Mixlist_NPCS.csv");
	remove("Mixlist_ITENS.csv");

	for (int i = 0; i < 100; i++)
	{
		char npcLine[1024];
		char itemLine[1024];

		sprintf(npcLine, "\nid=%d\nFace=%d\nGold=%d\nItem=%d,%d,%d,%d,%d,%d,%d",
			i,
			MixData.npcs[i].face,
			MixData.npcs[i].Gold,
			MixData.npcs[i].ItemSlot.Index,
			MixData.npcs[i].ItemSlot.EF1, MixData.npcs[i].ItemSlot.EFV1,
			MixData.npcs[i].ItemSlot.EF2, MixData.npcs[i].ItemSlot.EFV2, 
			MixData.npcs[i].ItemSlot.EF3, MixData.npcs[i].ItemSlot.EFV3);

		FilePuts("NPCS", npcLine);

		sprintf(npcLine, "Map=%d,%d",
			MixData.npcs[i].MapX,MixData.npcs[i].MapY);

		FilePuts("NPCS", npcLine);

		sprintf(npcLine, "Type=%d",
			MixData.npcs[i].Type);

		FilePuts("NPCS", npcLine);

		for (int b = 0; b < 8; b++)
		{
			sprintf(npcLine, "ItemRequire[%d]=%d,%d",
				b,
				MixData.npcs[i].Unknow[b].Req,
				MixData.npcs[i].Unknow[b].Value);

			FilePuts("NPCS", npcLine);
		}
		
		sprintf(npcLine, "Unk20=%d\nUnk24=%d\n",
			MixData.npcs[i].Unknow_20,
			MixData.npcs[i].Unknow_24);

		FilePuts("NPCS", npcLine);
		FilePuts("NPCS", "end;\n");

		/* ITENS */

		sprintf(itemLine, "id=%d\nItem=%d,%d,%d,%d,%d,%d,%d",
			i,
			MixData.Req[i].item.Index,
			MixData.Req[i].item.EF1, MixData.Req[i].item.EFV1,
			MixData.Req[i].item.EF2, MixData.Req[i].item.EFV2,
			MixData.Req[i].item.EF3, MixData.Req[i].item.EFV3);

		FilePuts("ITENS", itemLine);

		sprintf(itemLine, "Req=%d\nInterval=%d",
			MixData.Req[i].Amount, MixData.Req[i].Interval);

		FilePuts("ITENS", itemLine);

		sprintf(itemLine, "Strdef=%d",
			MixData.Req[i].Strdef);

		FilePuts("ITENS", itemLine);

		sprintf(itemLine, "Unk=%d\nUnused=%d\nUnused2=%d\n",
			MixData.Req[i].Unk, MixData.Req[i].Unused, MixData.Req[i].Unused_02);

		FilePuts("ITENS", itemLine);
		FilePuts("ITENS", "end;\n");
	}

	return true;
}

bool FileExists(const char *filename)
{
	FILE *arquivo;
	arquivo = fopen(filename, "rb");

	if (arquivo)
	{
		fclose(arquivo);
		return true;
	}

	return false;
}

npcCompleto GetContent()
{
	npcCompleto m_data;

	char mDir[256];
	sprintf(mDir, "Mixlist.bin");

	FILE *m_file = NULL;

	m_file = fopen(mDir, "rb");

	if (m_file == NULL)
	{
		return m_data;
	}

	fread(&m_data, sizeof(npcCompleto), 1, m_file);

	fclose(m_file);

	return m_data;
}


void FilePuts(char *mdir, char *mstr)
{
	FILE *f;
	char logDir[128];
	sprintf(logDir, "Mixlist_%s.csv", mdir);
	fopen_s(&f, logDir, "a+");

	if (f != NULL)
	{
		fprintf(f, "%s\n", mstr);
	}

	fclose(f);
}