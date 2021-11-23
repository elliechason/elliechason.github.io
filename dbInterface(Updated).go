//NOTE: This program was made by Elizabeth Chason and Cole Mathes under the Jefferson Lab High School Summer Honors Program 

package main

import "C"
import "database/sql"

func retrieveOwnersData(db *sql.DB, table_name string, travID string) (*sql.Rows, error) {
	return db.Query("SELECT * FROM :table_name WHERE TRAV_ID = :travID AND OBS IS NULL", "TRAV_OWNERS", table_name, travID)
}

func setConfigData(db *sql.DB, summation int, travID string) error {
	_, err := db.Query("UPDATE TRAV_CONFIG SET TRAV_SEQ_NUM=:summation WHERE TRAV_ID=:travID AND OBS IS NULL;", summation, travID)
	return err
}

func setOwnersData(db *sql.DB, inst instantiation) error {
	_, err := db.Query("INSERT INTO TRAV_CONFIG (MOD_USER, MOD_DATE, TRAV_REVISION, TRAV_SEQ_NUM, TRAV_COMPLETE, TRAV_CLOSE_WHO, OBS, TRAV_ID, D3ID, NCRID, TRAV_OPEN_DATE, TRAV_CLOSE_DATE, TRAV_OPEN_WHO) VALUES (:MOD_USER, :MOD_DATE, :TRAV_REVISION, :TRAV_SEQ_NUM, :TRAV_COMPLETE, :TRAV_CLOSE_WHO, :OBS, :TRAV_ID, :D3ID, :NCRID, :TRAV_OPEN_DATE, :TRAV_CLOSE_DATE, :TRAV_OPEN_WHO)", inst.ModUser, inst.ModDate, inst.TravRevision, inst.TravSeqNum, inst.TravComplete, inst.TravCloseWho, inst.OBS, inst.TravId, inst.D3ID, inst.NCRID, inst.TravOpenDate, inst.TravCloseDate, inst.TravOpenWho)
	return err
}

func getDataToMigrate(db *sql.DB, travFrom string, travTo string) (*sql.Rows, error){



	var res []string
	colNames, err := db.Query("SELECT DISTINCT B.Column_Name FROM All_Tab_Columns B FULL OUTER JOIN All_Tab_Columns A ON B.Column_Name = A.Column_Name AND A.Table_Name=:travFrom WHERE B.Table_Name=:travTo AND B.Column_Name IS NOT NULL", travfrom, travto)
	if err != nil {
		return nil, err
	}



	defer func(colNames *sql.Rows) {
		err := colNames.Close()
		if err != nil {

		}
	}(colNames)



	for colNames.Next(){
		var columnName string
		err := colNames.Scan(&columnName)
		if err != nil {
			return nil, err
		}
		res = append(res, columnName)
	}



	insertQuery := "INSERT INTO :travTo (?) SELECT T.* FROM :travFrom T, All_Tab_Columns C WHERE C.Column_Name IN (SELECT DISTINCT B.Column_Name FROM All_Tab_Columns B FULL OUTER JOIN All_Tab_Columns A ON B.Column_Name = A.Column_Name AND A.Table_Name=:travFrom WHERE B.Table_Name=:travTo AND B.Column_Name IS NOT NULL) AND C.Table_Name=:travTo"



	colData, err := db.Query(insertQuery, travto, res, travfrom, travfrom, travto, travto)
	if err != nil {
		return nil, err
	} else {
		return colData, nil
	}
}