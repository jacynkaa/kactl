
#usun repy
find content -type f -name "*.h" -print0 | xargs -0 sed -i "s/rep(/fwd(/g"

#zamien dwuargumentowe fwd na repy niestety czasem jest tam spacja a czasem nie
find content -type f -name "*.h" -print0 | xargs -0 sed -i "s/fwd(\(.\), 0/rep(\1/g"
find content -type f -name "*.h" -print0 | xargs -0 sed -i "s/fwd(\(.\),0/rep(\1/g"


#zamien PII na pii oraz VI na vi
find content -type f -name "*.h" -print0 | xargs -0 sed -i "s/Pii/pii/g"
find content -type f -name "*.h" -print0 | xargs -0 sed -i "s/Vi/vi/g"

#zamien pb na pushback
find content -type f -name "*.h" -print0 | xargs -0 sed -i "s/\.pb/.push_back/g"







